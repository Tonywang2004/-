#pragma once
#ifndef __AUDIOCONTROL_H__
#define __AUDIOCONTROL_H__

#include "audio/include/AudioEngine.h"
using namespace std;

class AudioControl {
public:
    // ȷ��ȫ�ֽ�����һ�� AudioControl ʵ��
    // ���þ�̬����
    static AudioControl* getInstance();

    // ���ű�������
    void playBackgroundMusic(const string& filename, bool loop = true);

    // ��������
    void setVolume(float volume);

    // ��ȡ��ǰ����
    float getVolume() const;

    // ������������
    void muteAllSounds();

    // ȡ��������������
    void unmuteAllSounds();

    // ��ȡ����״̬
    bool isMuted() const;
    
    //�����Ч
    void setClickSoundEnabled(bool enabled);
    bool isClickSoundEnabled() const;
    void playClickSoundEffect();

private:
    // ���캯��
    AudioControl();

    // ���þ�ָ̬��
    static AudioControl* instance;

    // �������ֵ���ƵID
    int backgroundMusicID;

    // ��ǰ����
    float currentVolume;

    // ����״̬��־
    bool isMute;

    //�����Ч��־
    bool isClickSound;
};

#endif 

