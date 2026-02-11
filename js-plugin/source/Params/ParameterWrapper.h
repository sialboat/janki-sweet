
#pragma once
#ifndef PARAMETER_WRAPPER
#define PARAMETER_WRAPPER

#include <JuceHeader.h>

class BaseParamWrapper
{
    public:
    virtual void prepareToPlay(double sampleRate, double duration - 0.05) noexcept = 0;
    virtual void reset() noexcept = 0;
    virtual void update() noexcept = 0;
    virtual void smoothen() noexcept = 0;

    virtual ~BaseParamWrapper() = default;
}

template <typename PARAM, typename T>
class ParamWrapper : public BaseParamWrapper
{
    protected:
    ParamWrapper(audioParam* _param,  const juce::ParameterID& _paramID, T init)
    : param(_param), paramID(_paramID), initValue(init), value(init) {}

    T getValue() { return value; }
    juce::LinearSmoothedValue<float> getSmoother() { return smoother; }
    juce::ParameterID getParamID() { return paramID; }
    PARAM* getParam() { return param; }

    protected:
    PARAM* param;
    const juce::ParameterID paramID;
    T initValue;
    T value;
    float mult = 1.0f;
};

template <typename PARAM, typename T>
class SmoothParamWrapper : public BaseParamWrapper
{
    protected:
    ParamWrapper(audioParam* _param, const juce::ParameterID& _paramID, T init)
    : param(_param), paramID(_paramID), initValue (init), value (init) {}
    
    T getValue() {return value;}
    juce::LinearSmoothedValue<float> getSmoother() {return smoother;}
    juce::ParameterID getParamID() {return paramID;}
    audioParam* getParam() {return param;}
    
    protected:
    audioParam* param;
    const juce::ParameterID paramID;
    juce::LinearSmoothedValue<float> smoother;
    T initValue;
    T value;
    float mult = 1.0f;
}

class FloatParamWrapper : public SmoothParamWrapper < juce::AudioParameterFloat, float>
{
    public:
    static std::unique_ptr<FloatParamWrapper> create(
        juce::AudioProcessorValueTreeState::ParameterLayout& layout,
        const juce::ParameterID& _paramID, const juce::String& name, 
        juce::NormalisableRange<float> range, float defaultValue, 
        const juce::AudioParameterFloatAttributes& attributes = {}, 
        float _mult = 1.0f
    ) {
        auto param = std::make_unique<juce::AudioParameterFloat>(_paramID, name, 
        range, defaultValue, attributes);

        auto* paramPtr = param.get();

        layout.add(std::move(param));

        return std::make_unique<FloatParamWrapper>(paramPtr, _paramID, smoother, defaultValue, _mult);
    }

    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override
    {
        this->duration = duration;
        smoother.reset(sampleRate, this->duration);
    }

    void reset() noexcept override
    {
        value = initValue;
        smoother.setCurrentAndTargetValue(param->get() * mult);
    }

    void update() noexcept override
    {
        smoother.setTargetValue(param->get() * mult);
    }

    void smoothen() noexcept override
    {
        value = smoother.getNextValue();
    }

    private:
    FloatParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, float _defaultValue)
    : ParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue) {
        smoother = juce::LinearSmoothedValue(_defaultValue);
    }

    FloatParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, float _defaultValue, float _mult = 1.0f)
    : ParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue) {
        smoother = juce::LinearSmoothedValue(_defaultValue);
        mult = _mult;
    }
};

class FloatGainParamWrapper : public SmoothParamWrapper <juce::AudioParameterFloat, float>
{
    public:
    static std::unique_ptr<FloatGainParamWrapper> create(
         juce::AudioProcessorValueTreeState::ParameterLayout& layout,
         const juce::ParameterID& _paramID, const juce::String& name,
         juce::NormalisableRange<float> range, float defaultValue,
         const juce::AudioParameterFloatAttributes &attributes = {}, float _mult = 1.0f)
       {
           auto param = std::make_unique<juce::AudioParameterFloat>(_paramID, name, range, defaultValue, attributes);

           auto* paramPtr = param.get();
//        auto smoother = juce::LinearSmoothedValue<float>(defaultValue);
        
           layout.add(std::move(param));

           return std::make_unique<FloatGainParamWrapper>(paramPtr, _paramID, smoother, defaultValue, _mult);
       }
    
    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override {
        smoother.reset(sampleRate, duration);
    }
    
    void reset() noexcept override {
        value = initValue;
        smoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(param->get() * mult));
    }
    
    void update() noexcept override {
        smoother.setTargetValue(juce::Decibels::decibelsToGain(param->get()) * mult);
    }
    
    void smoothen() noexcept override {
        value = smoother.getNextValue();
    }
    
    private:
    FloatGainParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, float _defaultValue)
    : ParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue) {
        smoother = juce::LinearSmoothedValue<float>(juce::Decibels::decibelsToGain(defaultValue));
    }
    
    FloatGainParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, float _defaultValue, float _mult) :
    ParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue) {
        smoother = juce::LinearSmoothedValue<float>(juce::Decibels::decibelsToGain(defaultValue));
        mult = _mult;
    }
};

class FloatExpParamWrapper : public SmoothParamWrapper <juce::AudioParameterFloat, float>
{
    public:
    
    static std::unique_ptr<FloatExpParamWrapper> create(
         juce::AudioProcessorValueTreeState::ParameterLayout& layout,
         const juce::ParameterID& _paramID, const juce::String& name,
         juce::NormalisableRange<float> range, float defaultValue, float target, float coeff,
         const juce::AudioParameterFloatAttributes &attributes = {}, float _mult = 1.0f)
       {
           auto param = std::make_unique<juce::AudioParameterFloat>(_paramID, name, range, defaultValue, attributes);

           auto* paramPtr = param.get();
           layout.add(std::move(param));

           return std::make_unique<FloatExpParamWrapper>(paramPtr, _paramID, defaultValue, _mult,  target, coeff);
       }
    
    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override
    {
        duration = 0.05;
        coeff = 1.0f - std::exp(-1.0f / (0.2f * float(sampleRate)));
    }
    
    void reset() noexcept override {
        value = initValue;
    }
    
    void update() noexcept override {
        target = param->get();
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
    
    FloatExpParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, float _defaultValue)
    : ParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue) {}
    
    FloatExpParamWrapper(juce::AudioParameterFloat* _param, const juce::ParameterID& _paramID, juce::LinearSmoothedValue<float> _smoother, float _defaultValue, float _mult, float _target, float _coeff)
    : ParamWrapper<juce::AudioParameterFloat, float>(_param, _paramID, _defaultValue), target(_target), coeff(_coeff) {
        smoother = std::move(_smoother);
        mult = _mult;
    }
};

class IntParamWrapper : public ParamWrapper<juce::AudioParameterInt, int>
{
    public:
    static std::unique_ptr<IntParamWrapper> create(
       juce::AudioProcessorValueTreeState::ParameterLayout& layout,
       const juce::ParameterID& _paramID, const juce::String& name,
       int minVal, int maxVal, int defaultVal, const juce::AudioParameterIntAttributes &attributes = {})
    {
        auto param = std::make_unique<juce::AudioParameterInt>(
        _paramID, name, minVal, maxVal, defaultVal, attributes);

        auto* paramPtr = param.get();
        layout.add(std::move(param));

        return std::make_unique<IntParamWrapper>(paramPtr, _paramID, defaultVal);
    }
    
    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override {}
    
    void update() noexcept override {value = param->get(); }
    
    void reset() noexcept override {value = initValue; }
    
    void smoothen() noexcept override {}
    
    private:
    IntParamWrapper(juce::AudioParameterInt* _param, const juce::ParameterID _paramID, int _defaultValue)
    : ParamWrapper<juce::AudioParameterInt, int>(_param, _paramID, _defaultValue) {}
};

class BoolParamWrapper : public ParamWrapper<juce::AudioParameterBool, bool>
{
    public:
    static std::unique_ptr<BoolParamWrapper> create(
        juce::AudioProcessorValueTreeState::ParameterLayout& layout,
        const juce::ParameterID& _paramID,const juce::String& name, bool defaultValue,
        const juce::AudioParameterBoolAttributes &attributes = {})
    {
        auto param = std::make_unique<juce::AudioParameterBool>(_paramID, name, defaultValue, attributes);

        auto* paramPtr = param.get();
        layout.add(std::move(param));

        return std::make_unique<BoolParamWrapper>(paramPtr, _paramID, defaultValue);
    }
    
    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override {}
    void smoothen() noexcept override {}
    
    void reset() noexcept override {value = initValue;}
    
    void update() noexcept override {value = !value;}
    
    private:
    BoolParamWrapper(juce::AudioParameterBool* _param, const juce::ParameterID& _paramID, bool _defaultValue)
    : ParamWrapper<juce::AudioParameterBool, bool>(_param, _paramID, _defaultValue) {}
};

class ChoiceParamWrapper : public ParamWrapper<juce::AudioParameterChoice, int>
{
    public:
    static std::unique_ptr<ChoiceParamWrapper> create(
          juce::AudioProcessorValueTreeState::ParameterLayout& layout,
          const juce::ParameterID& _paramID, const juce::String& name, const juce::StringArray &choices,
          int defaultIndex, const juce::AudioParameterChoiceAttributes &attributes = {})
    {
        auto param = std::make_unique<juce::AudioParameterChoice>(_paramID, name, choices, defaultIndex, attributes);

        auto* paramPtr = param.get();
        layout.add(std::move(param));

        return std::make_unique<ChoiceParamWrapper>(paramPtr, _paramID, defaultIndex);
    }
    
    void prepareToPlay(double sampleRate, double duration = 0.05) noexcept override {}
    void smoothen() noexcept override {}
    void reset() noexcept override {}
    
    void update() noexcept override {param->getIndex(); }
    
    private:
    ChoiceParamWrapper(juce::AudioParameterChoice* _param, const juce::ParameterID& _paramID, bool _defaultValue)
    : ParamWrapper<juce::AudioParameterChoice, int>(_param, _paramID, _defaultValue) {}
};