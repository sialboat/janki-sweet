#import "@preview/cheq:0.3.0": checklist
#import "@preview/fletcher:0.5.8" as fletcher: diagram, node, edge
#import "@preview/tdtr:0.2.0" : *
#show: checklist
#show link: underline


= janki sweet Nov 6 25 To Do:
Last updated: Nov 6 25 by Silas Wang

- [x] figure out how to share a repo
- [x] figure out what's gonna be in the janki sweet
  - [/] prioritize what we want to make in the janki sweet
- [/] Find resources (YouTubers, Textbooks, Websites, etc.)

*'le sweet*
- Gain / Utility
- Filters
- Spatial Panner or Stereo Width thing
- Reverb
- Compressor
- Granular Delay
- Minimeters visual stuff
- Distortion / Bitcrush / Redux
- Tremolo & Auto-Pan
- Amplifier?
- Delay
  - Phaser / Flanger
  
*tentative timeline:*

#diagram(spacing: 2em,$
 #rect(height: 8mm, "utility plugin") edge(->) & #rect(height: 8mm, "filters") edge(->) &#rect(height:8mm, "distortion") edge(->) &#rect(height: 8mm, "convolution & delay")

$)
\ \
#diagram(spacing:2em, $ 
  #rect(height: 8mm, "analysis (spectrogram, VU, oscilloscope, etc.)")
$)

=== resources
#link("https://brianmcfee.net/dstbook-site/content/intro.html")[Brian McFee's Digital Signals Thoery book] \
#link("https://www.youtube.com/@Lantertronics")[Lantertronics YouTube Channel] \
#link(" ")[DAFX Book (see the GitHub Repository)] \
#link(" ")[Miller Puckette's Electronic Music Theory Book (see GitHub repository)] \
#link("https://ccrma.stanford.edu/~jos/")[Julius Orion Smith III's CCRMA Website] \
#link("https://www.youtube.com/@3blue1brown")[3b1b]
- A `resources.md` text file will also be pushed to the GitHub alongside this one for us to keep track of resources.
- This current document is made using `Typst`, a typesetting language / programming language that compiles to a PDF / image. Documentation for Typst can be found at #link("https://typst.app/docs/")[typst.app/docs]
  - You don't have to use .typ, but the documents I push to the GitHub will be a `Typst` file and a `.pdf` file. 
  - You can use VSCode to write Typst documents by installing the `Tinymist` VSCode extension and create a `.typ` file.
  - `Command + K` then pressing `V` will let you see a live preview. You can export the current file by pressing the command `Command + P` and typing `>Typst: Export the opened file as PDF` or `>Typst: Export the opened file as Specified Format`.