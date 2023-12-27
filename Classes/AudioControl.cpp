#include "AudioControl.h"
#include "audio/include/AudioEngine.h"
#include "cocos2d.h"
#include"hero.h"
USING_NS_CC;

// ȷ��ȫ�ֽ�����һ�� AudioControl ʵ������ʵ�ֶ�ȫ�ֵ���������
// ��ʼ����̬ʵ��ָ��
AudioControl* AudioControl::instance = NULL;

// ���� AudioControl ��ĵ�һʵ��
AudioControl* AudioControl::getInstance() {
    // ���ʵ�������ڣ��򴴽���ʵ��
    if (instance == NULL) {
        instance = new AudioControl();
    }
    return instance;
}

// ���캯�������ó�ʼ״̬
AudioControl::AudioControl() : backgroundMusicID(-1), currentVolume(30.0f), isMute(false), isClickSound(true) {}

// ���ű�������
void AudioControl::playBackgroundMusic(const std::string& filename, bool loop) {
    if (backgroundMusicID != -1) {
        AudioEngine::stop(backgroundMusicID); // ֹͣ��ǰ���ŵ�����
    }
   // �����µı������ֲ�������ID
    backgroundMusicID = AudioEngine::play2d(filename, loop, currentVolume);
    isMute = false;
}

// ��������
void AudioControl::setVolume(float volume) {
    currentVolume = volume;
    if (backgroundMusicID != -1 ) {
        AudioEngine::setVolume(backgroundMusicID, volume); // ��������
    }
    isMute = false;
}

// ��ȡ��ǰ����
float AudioControl::getVolume() const {
    return currentVolume;
}

// ����
void AudioControl::muteAllSounds() {
    if (!isMute) {
        AudioEngine::setVolume(backgroundMusicID, 0); // ��������Ϊ 0 ʵ�־���
        isMute = true;
    }
}

// ȡ������
void AudioControl::unmuteAllSounds() {
    AudioEngine::setVolume(backgroundMusicID, currentVolume); // �ָ�����
    isMute = false;
}

// ��ȡ��ǰ����״̬
bool AudioControl::isMuted() const {
    return isMute;
}

//ͬ�������Ч����
void AudioControl::setClickSoundEnabled(bool enabled) {
    isClickSound = enabled;
}

bool AudioControl::isClickSoundEnabled() const {
    return !isClickSound;
}

void AudioControl::playClickSoundEffect() {
    if (isClickSound && !isMute) {
        AudioEngine::play2d("click_sound.mp3", false, currentVolume);
    }
}


