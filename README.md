# pilines

This is a realtime video processor, cvbs upscaler, which adds scanlines to the
original input signal. It is intended to be used on a Raspberry Pi, with an
easycap video capture stick.

## Background

During my last trip to Japan, I bought a couple of Famicom handheld clones
together with some games. These clones also have the ability to be connected
to the tv with cvbs. Unfortunately, though this works, it doesn't give that
retro-feeling it should give. On modern tv's, the cvbs signal looks choppy
and doesn't come close to the crt experience. This gave me the idea to, like
emulators, add scanlines to the picture, making the image looks more like an
old tv (which suits these consoles better).

## Dependencies

This little hack requires libav and SDL2 and is intended to be used without X11.
This implies you probably need to compile SDL2 yourself, as the SDL2 package
for raspbian does not support framebuffer rendering. ```make install_deps```
will help you with that ;-)

## Compatibility

Note that not all easycap sticks are supported by Linux, typically you want to
obtain one that contains the "STK1160" chipset.
