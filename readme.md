# Dependencies
* OpenFrameworks 0.10 ( https://openframeworks.cc/ )
* ofxXmlSettings
* ofxGpuParticles ( https://github.com/neilmendoza/ofxGpuParticles )
* ofxFft ( https://github.com/kylemcdonald/ofxFft)
* ofxDatGui ( https://github.com/braitsch/ofxDatGui )

# License
GPL v3

# Use
This guy basically makes particles out of the pixels in a video and pushes them around, using an attractor moved by the frequences detected in an audio feed.

Here's how you set it up:
* You name your video `video.mp4` and you drop it in `data/video/`. Every pixel will become a particle, so be considerate when it comes to resolution. Or, you know, just load an 8k video on a PI and enjoy 1fps while frying an egg on the device.
* `g` key toggles your gui, enabling you to fiddle with parameters
* `s` save the current configuration to file
* `l` reloads the last configuration you saved
* by default the audio input comes from device 0 on your system, whatever it is; howerver, if you have multiple sound interfaces, you'll see them listed at the bottom of your gui. They will be in the `[device_id] - [device_name]` format; if you want to change your input just edit the `<dev_id>` tag in `data/settings.xml` with the device id you want to use.

