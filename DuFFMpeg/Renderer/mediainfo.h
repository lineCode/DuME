﻿#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include <QObject>
#include <QRegularExpression>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>
#include <QDir>
#include <QTemporaryDir>

#include "FFmpeg/ffcodec.h"
#include "FFmpeg/ffmuxer.h"
#include "utils.h"

class MediaInfo : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief DuMediaInfo Constructs an empty MediaInfo
     * @param parent The QObject parent
     */
    explicit MediaInfo( QObject *parent = nullptr );

    /**
     * @brief DuMediaInfo Constructs a new MediaInfo from the output of the anaylisis given by `ffmpeg -i mediaFile` or `ffprobe mediaFile`
     * @param ffmpegOutput The output of the ffmpeg/ffprobe analysis
     * @param parent The QObject parent
     */
    explicit MediaInfo(QString ffmpegOutput, QObject *parent = nullptr);

    /**
     * @brief DuMediaInfo Constructs a new MediaInfo for the given file.
     * @param mediaFile The media file. For a frame sequence, it can be any frame from the sequence
     * @param parent The QObject parent
     */
    explicit MediaInfo(QFileInfo mediaFile, QObject *parent = nullptr);



    //setters

    /**
     * @brief updateInfo Updates all the information for this media file
     * @param mediaFile The media file. For a frame sequence, it can be any frame from the sequence
     */
    void updateInfo(QFileInfo mediaFile);
    /**
     * @brief updateInfo Updates all the information for this media from the output of ffprobe or ffmpeg
     * @param ffmpegOutput The output of ffprobe or ffmpeg when analyzing this media, as returned by `ffmpeg -i mediaFile` or `ffprobe mediaFile`.
     */
    void updateInfo(QString ffmpegOutput);

    void setMuxer(FFMuxer *muxer);
    void setContainer(QStringList container);
    void setVideoWidth(int width);
    void setVideoHeight(int height);
    void setVideoFramerate(double fps);
    void setAudioSamplingRate(int sampling);
    void setDuration(double duration);
    void setFileName(QString fileName);
    void setVideoCodec(FFCodec *codec);
    void setAudioCodec(FFCodec *codec);
    void setVideoBitrate(double bitrate, MediaUtils::BitrateUnit unit = MediaUtils::Bits);
    void setAudioBitrate(double bitrate, MediaUtils::BitrateUnit unit = MediaUtils::Bits);
    void setSize(double size, MediaUtils::SizeUnit unit = MediaUtils::Bytes);
    void setFFmpegOptions(QList<QStringList> options);
    void setVideo(bool video = true);
    void setAudio(bool audio = true);
    void setVideoProfile(int profile);
    void setVideoQuality(int quality);
    void setLoop(int loop);
    void addFFmpegOption(QStringList option);
    void removeFFmpegOptions(QString optionName);
    void clearFFmpegOptions();
    void setStartNumber(int startNumber);
    void setFrames(const QStringList &frames);
    void setPixFormat(FFPixFormat *pixFormat);
    void setPremultipliedAlpha(bool premultipliedAlpha);
    void setTrc(const QString &trc);
    void setAep(bool isAep);
    void setAepNumThreads(int aepNumThreads);
    void setAepCompName(const QString &aepCompName);
    void setAepRqindex(int aepRqindex);
    void setDurationH(int durationH);
    void setDurationM(int durationM);
    void setDurationS(double durationS);
    void setDurationF(int durationF);
    void setCacheDir(QTemporaryDir *cacheDir);
    void setAeUseRQueue(bool aeUseRQueue);
    //getters
    FFMuxer *muxer() const;
    int videoWidth();
    int videoHeight();
    double videoFramerate();
    int audioSamplingRate();
    double duration();
    QString ffmpegOutput();
    QString fileName();
    FFCodec *videoCodec();
    FFCodec *audioCodec();
    FFPixFormat *pixFormat();
    double audioBitrate(MediaUtils::BitrateUnit unit = MediaUtils::Bits);
    double videoBitrate(MediaUtils::BitrateUnit unit = MediaUtils::Bits);
    double size(MediaUtils::SizeUnit unit = MediaUtils::Bytes);
    QList<QStringList> ffmpegOptions();
    bool hasVideo();
    bool hasAudio();
    bool isImageSequence();
    QStringList extensions() const;
    int videoQuality() const;
    int videoProfile() const;
    int loop() const;
    int startNumber() const;
    QStringList frames() const;
    bool premultipliedAlpha() const;
    QString trc() const;
    bool isAep() const;
    QString aepCompName() const;
    int aepNumThreads() const;
    int aepRqindex() const;
    QTemporaryDir *cacheDir() const;
    bool aeUseRQueue() const;
    int durationH() const;
    int durationM() const;
    double durationS() const;
    int durationF() const;
    QString ffmpegSequenceName() const;

    //utils
    QString exportToJson();
    void exportToJson(QString jsonPath);
signals:

public slots:

private:

    // ========== ATTRIBUTES ==============

    /**
     * @brief _extensions The list of file extensions this media can use
     */
    QStringList _extensions;
    /**
     * @brief _muxer The muxer of this media file
     */
    FFMuxer *_muxer;
    /**
     * @brief _duration The duration in seconds
     */
    double _duration;
    /**
     * @brief _durationH The hours part of the duration
     */
    int _durationH;
    /**
     * @brief _durationM The minutes part of the duration
     */
    int _durationM;
    /**
     * @brief _durationS The seconds part of the duration
     */
    double _durationS;
    /**
     * @brief _durationI The frames part of the duration
     */
    int _durationF;
    /**
     * @brief _size The file size
     */
    int _size;
    /**
     * @brief _video Wether the file contains video
     */
    bool _video;
    /**
     * @brief _audio Wether the file contains audio
     */
    bool _audio;
    /**
     * @brief _imageSequence Wether this is a frame sequence instead of a single media file
     */
    bool _imageSequence;
    /**
     * @brief _videoCodec The norm or codec used for decoding or encoding the video
     */
    FFCodec *_videoCodec;
    /**
     * @brief _videoWidth The width in pixels
     */
    int _videoWidth;
    /**
     * @brief _videoHeight The height in pixels
     */
    int _videoHeight;
    /**
     * @brief _videoFramerate The framerate in frames per second
     */
    double _videoFramerate;
    /**
     * @brief _videoBitrate The video bitrate
     */
    int _videoBitrate;
    /**
     * @brief _pixFormat The pixel format
     */
    FFPixFormat *_pixFormat;
    /**
     * @brief _audioCodec The norm or codec used for decoding or encoding audio
     */
    FFCodec *_audioCodec;
    /**
     * @brief _audioSamplingRate The audio sampling in kHz
     */
    int _audioSamplingRate;
    /**
     * @brief _audioBitrate The audio bitrate
     */
    int _audioBitrate;
    /**
     * @brief _ffmpegOutput The analysis of the media as returned by ffprobe
     */
    QString _ffmpegOutput;
    /**
     * @brief _fileName The filename of the media
     */
    QString _fileName;
    /**
     * @brief _frames For a frame sequence, the list of all the frames filenames
     */
    QStringList _frames;
    /**
     * @brief _ffmpegOptions The custom options to be used by ffmpeg when decoding or encoding this media
     */
    QList<QStringList> _ffmpegOptions;
    /**
     * @brief _videoQuality The video quality, as used by some codecs like h264
     */
    int _videoQuality;
    /**
     * @brief _videoProfile The video profile, as used by some codecs like prores
     */
    int _videoProfile;
    /**
     * @brief _loop The number of loops to be encoded (-1 for inifite, available only with some specific formats like GIF)
     */
    int _loop;
    /**
     * @brief _startNumber The number of the first frame
     */
    int _startNumber;
    /**
     * @brief _premultipliedAlpha Wether the Alpha is premultiplied
     */
    bool _premultipliedAlpha;
    /**
     * @brief _trc The color transfer profile (gamma)
     */
    QString _trc;
    /**
     * @brief _isAep Wether this is an After Effects project (aep, aet or aepx)
     */
    bool _isAep;
    /**
     * @brief _aepNumThreads The number of threads to use when rendering this mediq with After Effects
     */
    int _aepNumThreads;
    /**
     * @brief _aepCompName The name of the composition in this After Effects project to render
     */
    QString _aepCompName;
    /**
     * @brief _aepRqindex The index of the render queue item in this After Effects project to render
     */
    int _aepRqindex;
    /**
     * @brief _aepTempDir A pointer to the cache for temporary transcoding and other files for this media
     */
    QTemporaryDir *_cacheDir;
    /**
     * @brief _aeUseRQueue Wether to launch the render queue when rendering the After Effects project, or render a specific composition or renderqueue item.
     */
    bool _aeUseRQueue;
    /**
     * @brief _sequenceName The name of the file sequence as used by ffmpeg
     */
    QString _ffmpegSequenceName;

    //======== METHODS =============

    /**
     * @brief reInit Reinit all to default values
     */
    void reInit();
    /**
     * @brief loadSequence Loads all the frames of the frame sequence
     */
    void loadSequence();

};

#endif // MEDIAINFO_H