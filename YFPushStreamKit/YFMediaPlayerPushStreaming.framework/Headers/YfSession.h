//
//  YfSession.h
//  YFMediaPlayerPushStreaming
//
//  Created by suntongmian@163.com
//  Copyright (c) 2015年 YunFan. All rights reserved.
//

/**
 * SDK current version : v4.3.5
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreVideo/CoreVideo.h>
#import <CoreMedia/CoreMedia.h>
#import "YfSessionCamera.h"

@class YfSession;

typedef void(^audioRecoderError)(NSString *error,OSStatus status);

typedef void(^PixelCallBack)(CVPixelBufferRef pixelbuffer);

typedef void(^gifCallBack)(CFURLRef GifFileURL);

typedef NS_ENUM(NSInteger, YfSessionState)
{
    YfSessionStateNone,
    YfSessionStatePreviewStarted,
    YfSessionStateStarting,
    YfSessionStateStarted,
    YfSessionStateEnded,
    YfSessionStateError
};

typedef NS_ENUM(NSInteger, YfCameraState)
{
    YfCameraStateFront,
    YfCameraStateBack
};

typedef NS_ENUM(NSInteger,YfOutPutImageOrientation){
    
    YfOutPutImageOrientationNormal,               //直屏
    YfOutPutImageOrientationLandLeftFullScreen,   //左全屏
    YfOutPutImageOrientationLandRightFullScreen   //右全屏
    
};

typedef NS_ENUM(int,YfTransportStyle){
    
    YfTransportNone,//默认TCP
    YfTransportUDP,//使用UDP
    YfTransportFEC//使用FEC    暂时弃用
    
};


@protocol YfSessionDelegate <NSObject>
@required
- (void) connectionStatusChanged: (YfSessionState) sessionState;


@optional
- (void)yfsessionUploadSpeed:(int32_t)uploadSpeed;

- (void)yfSessionSendSpeed:(CGFloat)send AndReceiveSpeed:(CGFloat)receiveSpeed;

- (void)yfSessionRunInfo:(NSString *)str;

@optional
- (void)yfPushStreamingCameraSource:(CVPixelBufferRef)pixelbuffer size:(size_t)pixelbufferSize;
//@required
//- (CVPixelBufferRef)yfPushStreamingCameraSourceOutput:(CVPixelBufferRef)pixelBufferRef size:(size_t)pixelBufferSize;
@end

@protocol YfSessionCameraSourceDataDelegate <NSObject>
- (void)cameraSourceData:(CVPixelBufferRef)pixelBufferRef size:(size_t)pixelBufferSize;
@end

@interface YfSession : NSObject
@property (nonatomic, readonly) YfSessionState rtmpSessionState;
@property (nonatomic, assign) id<YfSessionDelegate> delegate;
@property (nonatomic, assign) id<YfSessionCameraSourceDataDelegate> dataDelegate;

@property (nonatomic, strong, readonly) UIView* previewView; // 摄像头视图
@property (nonatomic, assign) YfCameraState cameraState; // 前后摄像头切换
@property (nonatomic, assign) BOOL          torch; // YES：闪光灯打开，NO：关闭

@property(nonatomic,assign)BOOL isBeautify; //YES 开启美颜 NO:关闭美颜 //默认无美颜

@property (nonatomic,assign) BOOL  IsAudioOpen;//YES:推流音频 NO:不推流音频   默认NO

@property (nonatomic,assign)BOOL isHeadPhonesPlay; //默认NO     打开为YES

@property (nonatomic, assign) YfSessionCameraBeautifulFilter beautyType;

//暂时弃用
@property (nonatomic,assign) BOOL IsAutoFitBitRate; //YES：自适应开启    NO默认 自适应关闭


@property (nonatomic,assign,readonly) int64_t m_bufferSize;  //当前缓存大小


@property (nonatomic,assign)BOOL isPlayerCameraMirror;   //默认镜像 YES


@property (nonatomic,assign)int uploadSpeedCountTime;

//开启云帆美颜(默认为相芯美颜)
@property (nonatomic, assign) BOOL isYFBeauty;

@property (nonatomic, assign,readonly) YfSessionCamera *videoCamera;

//自适应码率接口
@property (nonatomic, assign) BOOL isOpenAdaptaBitrate;

/**
 * 函数功能：获取SDK版本号
 * 返回值类型：NSString
 */
+ (NSString *) getYfSDKVersion;

/**
 * 函数功能：获取相机输出的图像数据
 * pixelBufferRef : 相机的图像数据
 */
- (void)receivePushStreamingCameraSourceOutput:(CVPixelBufferRef)pixelBufferRef size:(size_t)pixelBufferSize;
- (void)receivePushStreamingCameraSourceSBOutput:(CMSampleBufferRef)sampleBufferRef size:(size_t)sampleBufferSize;


/**
 * url : rtmp推流地址
 */
- (void) startRtmpSessionWithRtmpURL:(NSString*)url; // URL : url

/**
 * rtmpUrl :   本地录制地址
 * streamKey : 如果是本地录制 请填写格式 目前支持 @"mp4"  @"flv"
 */
- (void) startRtmpSessionWithURL:(NSString*) rtmpUrl
                    andStreamKey:(NSString*) streamKey; // URL: rtmpUrl/streamKey

/**
 * 停止rtmp session，不释放资源，会触发rtmp session结束通知
 */
- (void) endRtmpSession;

/**
 * 停止录制，不释放资源，会触发结束通知
 */
- (void) endRecord;

/**   
 * 停止rtmp session，不释放资源，不会触发rtmp session结束通知
 */
- (void) shutdownRtmpSession;
/**
 * 停止rtmp session，释放资源，不会触发rtmp session结束通知
 */
- (void) releaseRtmpSession;

/**
 *  网络错误／无网络的时候中断推流 更新推流器状态
 */
- (void)ShutErrorRtmpSession;

//手动聚焦点
- (void)focusAtPoint:(CGPoint)point;

//传入ip传
- (char *)GetDNSIP:(char *)ipStr;

//重新设置码率 （最低400000,小于默认为400000）
- (void)reSetBitarate:(int)bps;

//重新设置帧率
- (void)reSetFrameRate:(int)fps;
//开启log保存在本地Documents
- (void)openLog:(BOOL)isOpen;

/**
 * 函数功能：初始化推流参数
 * videoSize : 编码视频的宽度, 高度
 * captureSessionPreset :相机采集尺寸
 * fps       : 帧率
 * bps       : 码率
 * bufferTime : 推流缓存时间 默认推荐 3s  取值范围 2-8
 * isDropFrame :/YES 丢帧   NO:不丢帧
 * isOnlyAudioPushBuffer: 是否纯音频推流  默认0
 * audioRecoderError :音频录音出错回调
 * isOpenAdapta 开启/关闭 自适应码率
 * enableHEVC 是否开启H265推流（开启后底层自动判断iphone7以上设备且iOS11系统才会使用）
 */

- (instancetype) initWithVideoSize:(CGSize)videoSize sessionPreset:(NSString *)captureSessionPreset frameRate:(int)fps bitrate:(int)bps bufferTime:(int)bufferTime isUseUDP:(YfTransportStyle)transportStyle isDropFrame:(BOOL)isDropFrame YfOutPutImageOrientation:(YfOutPutImageOrientation)YfOutPutImageOrientation isOnlyAudioPushBuffer:(BOOL)isOnlyAudioPushBuffer audioRecoderError:(audioRecoderError)audioRecoderError isOpenAdaptBitrate:(BOOL)isOpenAdapta enableHEVC:(BOOL)enableHEVC;


@end
