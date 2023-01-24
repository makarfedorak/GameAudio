#include <al.h>
#include <alc.h>

ALuint loadSound(const std::string& filename) {
    ALuint buffer;
    alGenBuffers(1, &buffer);
    // Load sound data from file into the buffer
    // ...
    return buffer;
}

void playSound(ALuint buffer, const glm::vec3& position, float volume, float pitch) {
    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source, AL_GAIN, volume);
    alSourcef(source, AL_PITCH, pitch);
    alSource3f(source, AL_POSITION, position.x, position.y, position.z);
    alSourcePlay(source);
}

#include <sndfile.h>

void streamSound(const std::string& filename) {
    SNDFILE* file = sf_open(filename.c_str(), SFM_READ, &sfinfo);
    if (!file) {
        // Error opening file
        return;
    }
    // Set up OpenAL buffer and source
    // ...
    while (true) {
        // Read a chunk of audio data from the file
        sf_count_t count = sf_read_short(file, buffer, BUFFER_SIZE);
        if (count == 0) {
            break;
        }
        // Queue the buffer with the audio data
        alBufferData(buffer, format, buffer, count * sizeof(short), sfinfo.samplerate
