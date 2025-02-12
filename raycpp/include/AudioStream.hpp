#ifndef RAYLIB_CPP_INCLUDE_AUDIOSTREAM_HPP_
#define RAYLIB_CPP_INCLUDE_AUDIOSTREAM_HPP_

#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * AudioStream management functions
 */
class AudioStream : public ::AudioStream {
public:
    AudioStream(const ::AudioStream& music) { set(music); }

    AudioStream(
        rAudioBuffer* buffer = nullptr,
        rAudioProcessor* processor = nullptr,
        unsigned int sampleRate = 0,
        unsigned int sampleSize = 0,
        unsigned int channels = 0)
        : ::AudioStream{buffer, processor, sampleRate, sampleSize, channels} {
        // Nothing.
    }

    /**
     * Init audio stream (to stream raw audio pcm data)
     *
     * @throws raylib::RaylibException Throws if the AudioStream failed to load.
     */
    AudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels = 2) {
        Load(sampleRate, sampleSize, channels);
    }

    AudioStream(const AudioStream&) = delete;

    AudioStream(AudioStream&& other) {
        set(other);

        other.buffer = nullptr;
        other.processor = nullptr;
        other.sampleRate = 0;
        other.sampleSize = 0;
        other.channels = 0;
    }

    ~AudioStream() { Unload(); }

    GETTER(rAudioBuffer*, Buffer, buffer)
    GETTER(rAudioProcessor*, Processor, processor)
    GETTER(unsigned int, SampleRate, sampleRate)
    GETTER(unsigned int, SampleSize, sampleSize)
    GETTER(unsigned int, Channels, channels)

    AudioStream& operator=(const ::AudioStream& stream) {
        set(stream);
        return *this;
    }

    AudioStream& operator=(const AudioStream&) = delete;

    AudioStream& operator=(AudioStream&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.buffer = nullptr;
        other.processor = nullptr;
        other.sampleRate = 0;
        other.sampleSize = 0;
        other.channels = 0;

        return *this;
    }

    /**
     * Update audio stream buffers with data
     */
    AudioStream& Update(const void* data, int samplesCount) {
        ::RLUpdateAudioStream(*this, data, samplesCount);
        return *this;
    }

    /**
     * Unload audio stream and free memory
     */
    void Unload() {
        if (IsValid()) {
            ::RLUnloadAudioStream(*this);
        }
    }

    /**
     * Check if any audio stream buffers requires refill
     */
    bool IsProcessed() const { return ::RLIsAudioStreamProcessed(*this); }

    /**
     * Play audio stream
     */
    AudioStream& Play() {
        ::RLPlayAudioStream(*this);
        return *this;
    }

    /**
     * Pause audio stream
     */
    AudioStream& Pause() {
        ::RLPauseAudioStream(*this);
        return *this;
    }

    /**
     * Resume audio stream
     */
    AudioStream& Resume() {
        ::RLResumeAudioStream(*this);
        return *this;
    }

    /**
     * Check if audio stream is playing
     */
    bool IsPlaying() const { return ::RLIsAudioStreamPlaying(*this); }

    /**
     * Stop audio stream
     */
    AudioStream& Stop() {
        ::RLStopAudioStream(*this);
        return *this;
    }

    /**
     * Set volume for audio stream (1.0 is max level)
     */
    AudioStream& SetVolume(float volume = 1.0f) {
        ::RLSetAudioStreamVolume(*this, volume);
        return *this;
    }

    /**
     * Set pitch for audio stream (1.0 is base level)
     */
    AudioStream& SetPitch(float pitch) {
        ::RLSetAudioStreamPitch(*this, pitch);
        return *this;
    }

    /**
     * Set pan for audio stream (0.5 is centered)
     */
    AudioStream& SetPan(float pan = 0.5f) {
        ::RLSetAudioStreamPan(*this, pan);
        return *this;
    }

    /**
     * Default size for new audio streams
     */
    static void SetBufferSizeDefault(int size) { ::RLSetAudioStreamBufferSizeDefault(size); }

    /**
     * Audio thread callback to request new data
     */
    void SetCallback(::AudioCallback callback) { ::RLSetAudioStreamCallback(*this, callback); }

    /**
     * Attach audio stream processor to stream
     */
    void AttachProcessor(::AudioCallback processor) { ::RLAttachAudioStreamProcessor(*this, processor); }

    /**
     * Detach audio stream processor from stream
     */
    void DetachProcessor(::AudioCallback processor) { ::RLDetachAudioStreamProcessor(*this, processor); }

    /**
     * Retrieve whether or not the audio stream is ready.
     */
    bool IsValid() const { return ::RLIsAudioStreamValid(*this); }

    /**
     * Load audio stream (to stream raw audio pcm data)
     *
     * @throws raylib::RaylibException Throws if the AudioStream failed to load.
     */
    void Load(unsigned int SampleRate, unsigned int SampleSize, unsigned int Channels = 2) {
        Unload();
        set(::RLLoadAudioStream(SampleRate, SampleSize, Channels));
        if (!IsValid()) {
            throw RaylibException("Failed to load audio stream");
        }
    }
protected:
    void set(const ::AudioStream& stream) {
        buffer = stream.buffer;
        processor = stream.processor;
        sampleRate = stream.sampleRate;
        sampleSize = stream.sampleSize;
        channels = stream.channels;
    }
};
} // namespace raylib

using RAudioStream = raylib::AudioStream;

#endif // RAYLIB_CPP_INCLUDE_AUDIOSTREAM_HPP_
