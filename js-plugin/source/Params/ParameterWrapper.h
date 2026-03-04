// ParameterWrapper.h
#pragma once
#ifndef PARAMETER_WRAPPER_H
#define PARAMETER_WRAPPER_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <memory>
#include <atomic>
#include <cmath>
/*
    ParameterWrapper.h

    Header file that contains parameter wrappers for every kind of parameter. This allows for all parameters 
    to be created and added to the APVTS on one line, and for all parameters within an APVTS to be iterated
    on in a loop.

    ParameterWrappers abstract the following:
    - Juce AudioParameters: interacts with the APVTS and DSP processors to update values in real time
    - Juce LinearSmoothedValues: interacts with AudioParameters to smooth changes across parameter values.
    - Juce APVTS: for streamlining Parameter Creation and parameter updates
*/

//-------- Base interface-------
/*
    Base parameter wrapper outlining all the virtual functions that must be implemented for 
    the object to properly function.
*/
class BaseParamWrapper
{
    public:

    /* 
        initialize the Parameter and by linking the parameter values within the object
        to the assigned parameter in the APVTS.
    */
    virtual void init(juce::AudioProcessorValueTreeState& apvts) = 0;

    /*
        Juce boilerplate that I forgort
    */
    virtual void prepareToPlay(double sampleRate, double duration = 0.05) noexcept = 0;

    /*
        Resets a parameter to its default value
    */
    virtual void reset() noexcept = 0;

    /*
        how to update parameter value upon value change.
    */
    virtual void update() noexcept = 0;

    /*
        optionally apply a smoothing function to change in param values.  
    */
    virtual void smoothen() noexcept = 0;

    virtual ~BaseParamWrapper() = default;
};

//===========Non-smoothed wrapper==========
/* 
    ParamWrapper<JUCE::PARAMETER, TYPE>

    Base Parameter Wrapper class that does not account for a juce::LinearlySmoothedValue
    within its specification (hence there is no use to implement the smoothen function here). 
    Some parameters like AudioParameterBool or AudioParameterInt or AudioParameterChoice does
    not need a smoother so it is probably a good idea to include this so we don't have useless
    shit clogging our memory.
*/
template <typename PARAM, typename T>
class ParamWrapper : public BaseParamWrapper
{
    public:
    ParamWrapper(PARAM* _param,  const juce::ParameterID& _paramID, T init)
    : param(_param), paramID(_paramID), initValue(init), value(init) {}

    T getValue() { return value; }
    juce::ParameterID getParamID() { return paramID; }
    PARAM* getParam() { return param; }

    protected:
    PARAM* param;
    std::atomic<float>* rawValue;
    const juce::ParameterID paramID;
    T initValue;
    T value;
    float mult = 1.0f;
};

//=========Smoothed wrapper===========
/*
    SmoothParamWrapper<JUCE_AUDIO_PARAM, TYPE>

    Base Parameter Wrapper class that contains a Juce::LinearSmoothedValue<float>
    (most likely because this is used for floating point parameters) within the
    abstraction. 
*/
template <typename PARAM, typename T>
class SmoothParamWrapper : public BaseParamWrapper
{
    public:
    SmoothParamWrapper(PARAM* _param, const juce::ParameterID& _paramID, T init)
    : param(_param), paramID(_paramID), initValue (init), value (init) {}
    
    T getValue() {return value;}
    juce::LinearSmoothedValue<float> getSmoother() {return smoother;}
    juce::ParameterID getParamID() {return paramID;}
    PARAM* getParam() {return param;}
    
    protected:
    PARAM* param;
    const juce::ParameterID paramID;
    juce::LinearSmoothedValue<float> smoother;
    std::atomic<float>* rawValue;                    // raw value
    T initValue;                                // default value
    T value;                                    // smoothed value
    float mult = 1.0f;
};

// ========== Float (smoothed) ===============
/*
    FloatParamWrapper<AudioParameterFloat, float>

    Basic Float Parameter Wrapper that adheres to the Parameter Wrapper design goals 
    specified above.
*/
class FloatParamWrapper : public SmoothParamWrapper < juce::AudioParameterFloat, float>
{
    public:
    static std::unique_ptr<FloatParamWrapper> create(
        juce::AudioProcessorParameterGroup& group,
        const juce::ParameterID& _paramID, const juce::String& name, 
        juce::NormalisableRange<float> range, float defaultValue, 
        const juce::AudioParameterFloatAttributes& attributes = {}, 
        float _mult = 1.0f
    ) {
        auto param = std::make_unique<juce::AudioParameterFloat>(_paramID, name, 
        range, defaultValue, attributes);

        auto* paramPtr = param.get();

        group.addChild(std::move(param));

        return std::make_unique<FloatParamWrapper>(paramPtr, _paramID, defaultValue, _mult);
    }

    void init(juce::AudioProcessorValueTreeState& apvts) override
    {
        rawValue = apvts.getRawParameterValue(this->paramID.getParamID());
    }

    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override
    {
        // this->duration = duration;
        smoother.reset(sampleRate, duration);
    }

    void reset() noexcept override
    {
        value = initValue;
        if(rawValue != nullptr)
            smoother.setCurrentAndTargetValue(rawValue->load() * mult);
    }

    void update() noexcept override
    {
        if(rawValue != nullptr)
            smoother.setTargetValue(rawValue->load() * mult);
    }

    void smoothen() noexcept override
    {
        value = smoother.getNextValue();
    }

    // private:
    FloatParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, float _defaultValue)
    : SmoothParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue) {
        smoother = juce::LinearSmoothedValue(_defaultValue);
    }

    FloatParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, float _defaultValue, float _mult = 1.0f)
    : SmoothParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue) {
        smoother = juce::LinearSmoothedValue(_defaultValue);
        mult = _mult;
    }
};


// =============== Gain in dB -> linear (smoothed) =========================
/*
    FloatGainParamWrapper<juce::AudioParameterFloat, float>

    Float Parameter Wrapper specifically tailored to abstracting gain-related parameters
    by utilizing gain-conversion functions.

    TODO: when not lazy, replace juce::Decibels functions to the functions in decibel_conversions.h
*/
class FloatGainParamWrapper : public SmoothParamWrapper <juce::AudioParameterFloat, float>
{
    public:
    static std::unique_ptr<FloatGainParamWrapper> create(
         juce::AudioProcessorParameterGroup& group,
         const juce::ParameterID& _paramID, const juce::String& name,
         juce::NormalisableRange<float> range, float defaultValue,
         const juce::AudioParameterFloatAttributes &attributes = {}, float _mult = 1.0f)
       {
           auto param = std::make_unique<juce::AudioParameterFloat>(_paramID, name, range, defaultValue, attributes);

           auto* paramPtr = param.get();
//        auto smoother = juce::LinearSmoothedValue<float>(defaultValue);
        
           group.addChild(std::move(param));

           return std::make_unique<FloatGainParamWrapper>(paramPtr, _paramID, defaultValue, _mult);
       }

    void init(juce::AudioProcessorValueTreeState& apvts) override
    {
        rawValue = apvts.getRawParameterValue(this->paramID.getParamID());
    }

    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override {
        smoother.reset(sampleRate, duration);
    }
    
    void reset() noexcept override {
        value = initValue;

        if(rawValue != nullptr)
            smoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(rawValue->load() * mult));
    }
    
    void update() noexcept override {
        if(rawValue != nullptr)
            smoother.setTargetValue(juce::Decibels::decibelsToGain(rawValue->load()) * mult);
    }
    
    void smoothen() noexcept override {
        value = smoother.getNextValue();
    }
    
    // private:
    FloatGainParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, float _defaultValue)
    : SmoothParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue) {
        smoother = juce::LinearSmoothedValue<float>(juce::Decibels::decibelsToGain(_defaultValue));
    }
    
    FloatGainParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, float _defaultValue, float _mult) :
    SmoothParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue) {
        smoother = juce::LinearSmoothedValue<float>(juce::Decibels::decibelsToGain(_defaultValue));
        mult = _mult;
    }
};



/*
    FloatExpParameterWrapper

    Float ParameterWrapper that is specifically tailored to a custom smoothing function
    that is different from juce::LinearSmoothedFunction.
*/
class FloatExpParamWrapper : public ParamWrapper <juce::AudioParameterFloat, float>
{
    public:
    
    static std::unique_ptr<FloatExpParamWrapper> create(
         juce::AudioProcessorParameterGroup& group,
         const juce::ParameterID& _paramID, const juce::String& name,
         juce::NormalisableRange<float> range, float defaultValue, float target, float coeff,
         const juce::AudioParameterFloatAttributes &attributes = {}, float _mult = 1.0f)
       {
           auto param = std::make_unique<juce::AudioParameterFloat>(_paramID, name, range, defaultValue, attributes);

           auto* paramPtr = param.get();
           group.addChild(std::move(param));

           return std::make_unique<FloatExpParamWrapper>(paramPtr, _paramID, defaultValue, _mult, target, coeff);
       }
    
    void init(juce::AudioProcessorValueTreeState& apvts) override
    {
        rawValue = apvts.getRawParameterValue(this->paramID.getParamID());
    }

    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override
    {
        duration = 0.05;
        coeff = 1.0f - std::exp(-1.0f / (0.2f * float(sampleRate)));
    }
    
    void reset() noexcept override {
        if (rawValue != nullptr) {
            target = rawValue->load();
            value = target; 
        } else {
            value = initValue;
            target = initValue;
        }
    }
    
    void update() noexcept override {
        if(rawValue != nullptr) {
            target = rawValue->load();
        }
        if(value == 0.0f) {
            value = target;
        }
    }
    
    void smoothen() noexcept override {
        value += (target - value) * coeff;
    }
    
    void setTarget (float val) {target = val;}
    void setCoeff (float val) {coeff = val;}
    float getTarget() {return target;}
    float getCoeff() {return coeff;}
    
    private:
    float target = 0.0f;
    float coeff = 0.0f;
    
    public:
    FloatExpParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, float _defaultValue)
    : ParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue) {}
    
    FloatExpParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, float _defaultValue, float _mult, float _target, float _coeff)
    : ParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue), target(_target), coeff(_coeff) {
        // smoother = juce::LinearSmoothedValue<float>(_defaultValue);
        mult = _mult;
    }
};

//================= Int (not smoothed) ==================
/*
    IntParamWrapper

    Parameter Wrapper that abstracts an Integer Parameter based on the
    design specifications mentioned above.
*/
class IntParamWrapper : public ParamWrapper<juce::AudioParameterInt, int>
{
    public:
    static std::unique_ptr<IntParamWrapper> create(
       juce::AudioProcessorParameterGroup& group,
       const juce::ParameterID& _paramID, const juce::String& name,
       int minVal, int maxVal, int defaultVal, const juce::AudioParameterIntAttributes &attributes = {})
    {
        auto param = std::make_unique<juce::AudioParameterInt>(
        _paramID, name, minVal, maxVal, defaultVal, attributes);

        auto* paramPtr = param.get();
        group.addChild(std::move(param));

        return std::make_unique<IntParamWrapper>(paramPtr, _paramID, defaultVal);
    }

    void init(juce::AudioProcessorValueTreeState& apvts) override
    {
        rawValue = apvts.getRawParameterValue(this->paramID.getParamID());
    }
    
    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override {}
    
    void update() noexcept override {
        if(rawValue != nullptr)
            value = static_cast<int>(std::round(rawValue->load()));
    }
    
    void reset() noexcept override { value = initValue; }
    
    void smoothen() noexcept override {}
    
    // private:
    IntParamWrapper(juce::AudioParameterInt* _param, const juce::ParameterID _paramID, int _defaultValue)
    : ParamWrapper<juce::AudioParameterInt, int>(_param, _paramID, _defaultValue) {}
};

//================= Bool (not smoothed) ==================
/*
    BoolParamWrapper

    Parameter Wrappers abstracting a Boolean Audio Parameter
*/
class BoolParamWrapper : public ParamWrapper<juce::AudioParameterBool, bool>
{
    public:
    static std::unique_ptr<BoolParamWrapper> create(
        juce::AudioProcessorParameterGroup& group,
        const juce::ParameterID& _paramID,const juce::String& name, bool defaultValue,
        const juce::AudioParameterBoolAttributes &attributes = {})
    {
        auto param = std::make_unique<juce::AudioParameterBool>(_paramID, name, defaultValue, attributes);

        auto* paramPtr = param.get();
        group.addChild(std::move(param));

        return std::make_unique<BoolParamWrapper>(paramPtr, _paramID, defaultValue);
    }

    void init(juce::AudioProcessorValueTreeState& apvts) override
    {
        rawValue = apvts.getRawParameterValue(this->paramID.getParamID());
    }
    
    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override {}
    void smoothen() noexcept override {}
    
    void reset() noexcept override {
        value = initValue;
    }
    
    void update() noexcept override {
        if(rawValue != nullptr)
            value = rawValue->load() >= 0.5;
    }
    
    // private:
    BoolParamWrapper(juce::AudioParameterBool* _param, const juce::ParameterID& _paramID, bool _defaultValue)
    : ParamWrapper<juce::AudioParameterBool, bool>(_param, _paramID, _defaultValue) {}
};

//================= Choice (not smoothed) ==================
/*
    ChoiceParamWrapper

    Parameter Wrapper abstracting the juce::AudioParameterChoice parameter, fairly similar
    to the juce::AudioParameterInt with the exception that I believe you can also specify
    an array of values / whatnot for this one to scan through.
*/
class ChoiceParamWrapper : public ParamWrapper<juce::AudioParameterChoice, int>
{
    public:
    static std::unique_ptr<ChoiceParamWrapper> create(
          juce::AudioProcessorParameterGroup& group,
          const juce::ParameterID& _paramID, const juce::String& name, const juce::StringArray &choices,
          int defaultIndex, const juce::AudioParameterChoiceAttributes &attributes = {})
    {
        auto param = std::make_unique<juce::AudioParameterChoice>(_paramID, name, choices, defaultIndex, attributes);

        auto* paramPtr = param.get();
        group.addChild(std::move(param));

        return std::make_unique<ChoiceParamWrapper>(paramPtr, _paramID, defaultIndex);
    }

    void init(juce::AudioProcessorValueTreeState& apvts) override
    {
        rawValue = apvts.getRawParameterValue(this->paramID.getParamID());
    }
    
    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override {}
    void smoothen() noexcept override {}
    void reset() noexcept override {}
    
    void update() noexcept override {
        if(rawValue != nullptr)
            value = static_cast<int>(std::round(rawValue->load()));
    }
    
    // private:
    ChoiceParamWrapper(juce::AudioParameterChoice* _param, const juce::ParameterID& _paramID, int _defaultValue)
    : ParamWrapper<juce::AudioParameterChoice, int>(_param, _paramID, _defaultValue) {}
};

#endif