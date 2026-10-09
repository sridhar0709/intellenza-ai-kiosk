# INTELLENZA 2K26 AI Reception Kiosk

A phone-first, zero-paid-API prototype for the INTELLENZA 2K26 symposium.

## Current features

- Responsive kiosk-style reception screen
- Animated robot face
- Browser speech synthesis for spoken answers
- Browser speech recognition when supported by the browser/device
- Typed question fallback
- Rule-based answers from a small, editable event knowledge base
- No API keys or paid AI services required

## Run and test

1. Open the deployed HTTPS site in Chrome on Android.
2. Tap **Welcome message** and allow speech playback.
3. Tap **Ask by voice** and grant microphone permission if prompted.
4. If voice recognition is unsupported, type questions in the input field.
5. Try: "What are the event dates?", "How much is the workshop?", and "Where is the workshop?"

Speech recognition support and offline behavior vary by browser. Text-to-speech is separate from speech recognition. The current app is rule-based, not a generative AI model.

## Event information

- 14 October 2026: Technical symposium
- 15 October 2026: Trends in Cybersecurity workshop
- Announced fees: symposium ₹250, workshop ₹200, both days ₹400
- Workshop venue announced as Seminar Hall, Shreenivasa Engineering College
- Previously announced registration deadline: 12 October 2026. Confirm with organizers whether registration is still open.

Verify event facts before public use.

## Hardware roadmap

The first version runs on the Android phone only. NodeMCU ESP8266 ESP-12E and Arduino Uno are not yet connected. The next hardware phase should add an optional Wi-Fi status endpoint or physical welcome button after choosing a network design compatible with the phone's HTTPS page and browser security restrictions.

Never put private credentials or API secrets in `index.html` or a public repository.
