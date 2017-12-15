//
//  YfSessionCamera.h
//  YfCamera
//
//  Created by 张涛 on 2017/3/25.
//  Copyright © 2017年 张涛. All rights reserved.
//



#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

typedef void(^gifCallBack)(CFURLRef GifFileURL);

typedef void(^PixelBufferCallBack)(CVPixelBufferRef pixelbuffer);



typedef NS_ENUM(NSInteger,YfSessionCameraInputDataSourceType){

    YfSessionCameraInputDataSourceTypeInputCamera = 0,    //使用内置摄像头数据
    
    YfSessionCameraInputDataSourceTypeOuterInputSource, //使用外置数据
    
};


typedef NS_ENUM(NSInteger,YfSessionCameraOrientation){

    YfSessionCameraOrientationNormal   = 0,
    YfSessionCameraOrientationLandLeftFullScreen,
    YfSessionCameraOrientationRightFullScreen
    
};


typedef NS_ENUM (NSInteger,YfSessionCameraBoxViewFilterFilter)
{
    
    YfSessionCameraBoxViewFilterFilterNone = 0,    //
    YfSessionCameraBoxViewFilterFilterFour,    //4宫格
    YfSessionCameraBoxViewFilterFilterNine,    //9宫格
};


typedef NS_ENUM (NSInteger,YfSessionCameraMirrorFilter)
{
      YfSessionCameraMirrorFilterNone = 0,
    
      YfSessionCameraMirrorFilterUpDown,
    
      YfSessionCameraMirrorFilterRightLeft,
};


typedef NS_ENUM (NSInteger,YfSessionCameraSpecialFilter)
{
    YfSessionCameraSpecialFilterNone = 0,
    
    YfSessionCameraSpecialFilterLine,
    
//    YYfSessionCameraMirrorFilterRightLeft,
};



typedef NS_ENUM(NSInteger,YfSessionCameraBeautifulFilter){
    
    YfSessionCameraBeautifulFilterNone  = 0,               //无美颜效果
    YfSessionCameraBeautifulFilterGlobalBeauty,       //全局美颜
    YfSessionCameraBeautifulFilterLocalSkinBeauty,    //局部皮肤美颜
    
};


typedef NS_ENUM(NSInteger,YfSessionCameraFilter){
    
    YfSessionCameraFilterNormal   = 0,
    YfSessionCameraFilterFishEye,                //鱼 眼
    YfSessionCameraFilterConcaveMirror,          //凹面镜
    YfSessionCameraFilterMagicMirror,            //哈哈镜
    YfSessionCameraFilterGlassSphere,            //水晶球
    YfSessionCameraFilterSwirl,                  //漩涡
    YfSessionCameraFilterCameo,                  //浮雕
    YfSessionCameraFilterVignette,               //晕影。
    YfSessionCameraFilterCartoon,                //漫画效果
    YfSessionCameraFilterMarz,                   //火星文
    YfSessionCameraFilterCloud,                  //云雾
    YfSessionCameraFilterColorOffSet,            //偏振
    YfSessionCameraFilterInterferenceEffect,     //随机噪点
    YfSessionCameraFilterOrangeBlue,             //橘色化
    YfSessionCameraFilterWave,                   //波浪
    //开销高
    YfSessionCameraFilterBroken,                  //碎裂
    YfSessionCameraFilterFakeRipple,              //重影抖动
    YfSessionCameraFilterFakeHole,                //洞
    YfSessionCameraFilterSobelLine,                //线条
    YfSessionCameraFilterNightNoise,              //随机噪点抖动
    YfSessionCameraFilterSeparateRGB,              //色彩分离
    YfSessionCameraFilterRain,                   //下雨
    YfSessionCameraFilterNightVision,             //夜视
    YfSessionCameraFilterSevenTyLine,             //横纹
    YfSessionCameraFilterBlackWhiteTV,            //黑白卡顿闪屏电视
    YfSessionCameraFilterBlackColorTV,            //彩色卡顿闪屏电视
    YfSessionCameraFilterBlackWhite2TV,            //黑白卡顿闪屏电视
    YfSessionCameraFilterBokehBlur,                    //渐变模糊
    //高开销
    YfSessionCameraFilterBroken2,                       //碎裂2
    //低开销 常规
    YfSessionCameraFilterFourBoxFilterNormal,                //四宫格
    //低开销 特效
    YfSessionCameraFilterFourBoxFilterSpecial,               //特效四宫格
    //低开销 常规
    YfSessionCameraFilterNineBoxFilterNormal,                //九宫格
    //低开销 特效
    YfSessionCameraFilterNineBoxFilterSpecial,                //九宫格
    
    
};

typedef enum : NSUInteger {
    
    YfSessionCameraLogoPostitionleftUp = 0,
    YfSessionCameraLogoPostitionleftDown,
    YfSessionCameraLogoPostitionrightUp,
    YfSessionCameraLogoPostitionrightDown,
    
} YfSessionCameraLogoPostition;


typedef enum {
    
    YFINSTCamera_NORMAL_FILTER = 0,
    
    YFINSTCamera_AMARO_FILTER,
    
    YFINSTCamera_RISE_FILTER,
    
    YFINSTCamera_HUDSON_FILTER,
    
    YFINSTCamera_XPROII_FILTER,
    
    YFINSTCamera_SIERRA_FILTER,
    
    YFINSTCamera_LOMOFI_FILTER,
    
    YFINSTCamera_EARLYBIRD_FILTER,
    
    YFINSTCamera_SUTRO_FILTER,
    
    YFINSTCamera_TOASTER_FILTER,
    
    YFINSTCamera_BRANNAN_FILTER,
    
    YFINSTCamera_INKWELL_FILTER,
    
    YFINSTCamera_WALDEN_FILTER,
    
    YFINSTCamera_HEFE_FILTER,
    
    YFINSTCamera_VALENCIA_FILTER,
    
    YFINSTCamera_NASHVILLE_FILTER,
    
    YFINSTCamera_1977_FILTER,
    
    YFINSTCamera_LORDKELVIN_FILTER,
    
} YFINSTCameraFilterType;


//Delegate Protocal for Face Detection.
@protocol YfSessionCameraDelegate <NSObject>


//原始相机数据  可在此处自定义处理数据 添加各种滤镜
@optional
- (CVPixelBufferRef)willOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer;

//美颜处理后的数据
- (void)willOutputPixelBuffer:(CVPixelBufferRef)PixelBuffer pts:(int64_t)pts;
@end


@interface YfSessionCamera : NSObject<AVCaptureVideoDataOutputSampleBufferDelegate,AVCaptureMetadataOutputObjectsDelegate>

{
    AVCaptureSession *_captureSession;
    AVCaptureDevice *_inputCamera;
    AVCaptureDeviceInput *videoInput;
    AVCaptureVideoDataOutput *videoOutput;
    
   // AVCaptureMetadataOutput *metaDataOutput;
    
    //第一帧渲染信号
    //dispatch_semaphore_t frameRenderingSemaphore;
    //是否需要停止
    BOOL capturePaused;
}


/**
 * 函数功能：获取SDK版本号
 * 返回值类型：NSString
 */

+ (NSString *)YfSessionCameraVersion;


/** Begin a capture session
 
 See AVCaptureSession for acceptable values
 
 @param sessionPreset Session preset to use
 @param cameraPosition Camera to capture from
 @param YfSessionCameraOrientation OutputImageOrientation
 @parm  outputBufferSize    the size of preview outputbuffer
 */
- (id)initWithSessionPreset:(NSString *)sessionPreset cameraPosition:(AVCaptureDevicePosition)cameraPosition YfSessionCameraOrientation:(YfSessionCameraOrientation)YfSessionCameraOrientation outputBufferSize:(CGSize)outputBufferSize YfSessionCameraInputDataSourceType:(YfSessionCameraInputDataSourceType)InputDataSourceType;


/** Get the AVCaptureConnection of the source camera
 */
@property (readonly,strong)AVCaptureConnection *connection;

// The capture session preview
@property(readonly,nonatomic) UIView *preview;

/// Whether or not the underlying AVCaptureSession is running
@property(readonly, nonatomic) BOOL isRunning;


@property(nonatomic, assign) id<YfSessionCameraDelegate> delegate;

/// Use this property to manage camera settings. Focus point, exposure point, etc.
@property(readonly) AVCaptureDevice *inputCamera;

/// The AVCaptureSession used to capture from the camera
@property(readonly, retain, nonatomic) AVCaptureSession *captureSession;

/// This enables the capture session preset to be changed on the fly
@property (readwrite, nonatomic, copy) NSString *captureSessionPreset;


//Playback and push the end of the preview layer is mirroring
@property (nonatomic, assign)BOOL  isPlayerCameraMirror;

//雪景。 //暂时弃用
@property (nonatomic, assign)BOOL  snowSceneOpen;


/**内部控制长亮
 */
@property (nonatomic, assign)BOOL iskeepOnlightWhenCapturing;


//设置数据输入源
@property (nonatomic, readwrite)YfSessionCameraInputDataSourceType InputDataSourceType;




//set camera torch
@property (nonatomic, assign) BOOL          torch;

/// This sets the frame rate of the camera (iOS 5 and above only)
/**
 Setting this to 0 or below will set the frame rate back to the default setting for a particular preset.
 */
@property (readwrite) int32_t frameRate;

/** Get the position (front, rear) of the source camera
 */
- (AVCaptureDevicePosition)cameraPosition;


/** add a logo to capture session preview
 @param filePath   Logo filePatch to use
 @param YfSessionCameraLogoPostition  Camera Logo Postition to use
 */

//弃用。  2017-8-18   替代方法 - (void)drawImageTexture:(NSString *)filePath PointRect:(CGRect)PointRect;
- (void)drawImageTexture:(NSString *)filePath PointSize:(YfSessionCameraLogoPostition)YfSessionCameraLogoPostition;


/** add a logo to capture session preview
 @param filePath   Logo filePatch to use
 @param PointRect  Camera Logo Rect to use
 */
- (void)drawImageTexture:(NSString *)filePath PointRect:(CGRect)PointRect;

/**
 Remove logo from capture session preview
 */
- (void)removeLogo;

/**
 Get a UIimage from session preview
 */
- (UIImage *)snapshot;



//开启gif显示
-(void)decodeAndRenderWithFilePath:(NSString *)filePath PointRect:(CGRect)PointRect;
//关闭gif显示 && 释放
- (void)closeAndCleanGif;




//player preview scale
- (void)setScaleX:(float)xscale Y:(float)yscale Z:(float)zscale;


//选取几秒内 几张图片
- (void)createGifSnapShotDelayTime:(float)SnapShotDelayTime ImageCount:(int)ImageCount gifDelayTime:(float)delayTime gifFileName:(NSString*)gifFileName  gifCallBack:(gifCallBack)GifCallBack;


- (void)createGifImageArr:(NSArray<UIImage *> *)ImageArr gifDelayTime:(float)delayTime gifFileName:(NSString*)gifFileName  gifCallBack:(gifCallBack)GifCallBack;


//Use pinggesture UIPinchGestureRecognizer's scale to set
- (void)SetVideoZoom:(float)zoom;

//enable touch
//Use current touch point to set

//手动聚焦点
- (void)focusAtPoint:(CGPoint)point;

//手动曝光
- (void)ExposureAtPoint:(CGPoint)point;


/** Resume camera capturing
 */
- (void)resumeCameraCapture;

/** Pause camera capturing
 */
- (void)pauseCameraCapture;

/** Stop camera capturing
 */
- (void)stopCameraCapture;

/** Start camera capturing
 */
- (void)startCameraCapture;

/** This flips between the front and rear cameras
 */
- (void)rotateCamera;

/**Release Camera Source
 */
- (void)releaseCamera;

// set camera exposure
- (BOOL)setupContinuousExposure:(BOOL)wantsContinuous;


//锐化设置 针对所有美颜效果
// Sharpness ranges from -4.0 to 4.0, with 0.0 as the normal level
- (void)setSharpnessLevel:(float)SharpnessLevel;


#pragma mark-------------针对YfSessionCameraBeautifulFilterGlobalBeauty进行属性修改-----
//值越大越红润。 default is 0.1
//set beatiful rouguang 0.0 - 1.0  //红润
- (void)setRouGuangLevel:(float)RouGuangLevel;
//值越小。磨皮程度越高 default is 0.3
//set beatiful Blur 0.0 - 1.0
- (void)setBlurLevel:(float)BlurLevel;
//饱和度值越大 程度越高 default is 0.3
//set beatiful Saturation 0.0 - 1.0
- (void)setSaturationLevel:(float)SaturationLevel;
// brightness ranges from -0.5 to 1.0, with 0.0 as the normal level
- (void)setBrightNessLevel:(float)BrightNessLevel;


#pragma mark-------------针对YfSessionCameraBeautifulFilterLocalSkinBeauty进行属性修改-----

//色温
//The hue rotation is in the range [-360, 360] with 0 being no-change.
//default is -0.88
- (void)rotateHue:(float)h;

//饱和度
//The saturation adjustment is in the range [0.0, 2.0] with 1.0 being no-change.
//default is 1.0
- (void)adjustSaturation:(float)s;

//The brightness adjustment is in the range [0.0, 2.0] with 1.0 being no-change.
//default is 1.0;
- (void)adjustBrightness:(float)b;

//曝光度
// Exposure ranges from -10.0 to 10.0, with 0.0 as the normal level
//default is 0.0
- (void)adjustExposureness:(float)e;

//白平衡
//choose color temperature, in degrees Kelvin
//default 5000
- (void)adjustTemperatureness:(float)t;
//磨皮程度
//default is 3.8
- (void)adjustBlurness:(float)b;

//红润度
//The ruddiness adjustment is in the range [0.0, 1.0] with 0.0 being no-change.
//default is 0.3
- (void)adjustRuddiness:(float)r;




//set camera filter   //创意滤镜
- (void)setupFilter:(YfSessionCameraFilter)filter;


//ins 滤镜   default is  YFINSTCamera_NORMAL_FILTER。     //画质滤镜。
- (void)switchFilter:(YFINSTCameraFilterType)type;


//切换美颜效果
- (void)switchBeautyFilter:(YfSessionCameraBeautifulFilter)BeautyFilter;


//设置宫格信息
- (void)switchBOXViewsFilter:(YfSessionCameraBoxViewFilterFilter)BoxViewFilterFilter;


//设置镜像特效
- (void)switchMirrorFilter:(YfSessionCameraMirrorFilter)MirrorFilter;

//设置特殊滤镜
- (void)switchSpecialFilter:(YfSessionCameraSpecialFilter)SpecialFilter;






//接受yuv和rgba   420v 420f 适用于硬解
//接受yuv和rgba
- (void)receivePixelbufferTextureAtBufferIndex_0:(CVPixelBufferRef)piexelbuffer displayRect:(CGRect)displayRect;
- (void)CleanbufferTextureAtBufferIndex_0;

- (void)receivePixelbufferTextureAtBufferIndex_1:(CVPixelBufferRef)piexelbuffer displayRect:(CGRect)displayRect;
- (void)CleanbufferTextureAtBufferIndex_1;

- (void)receivePixelbufferTextureAtBufferIndex_2:(CVPixelBufferRef)piexelbuffer displayRect:(CGRect)displayRect;
- (void)CleanbufferTextureAtBufferIndex_2;


- (void)cleanAllYUVRGBAPixelbufferTexture;

//y u v三通道 适用于软解    //CGSize宽高  spanSize多于出来的像素跨度
- (void)receiveYUVTextureY:(void*)yData U:(void*)uData V:(void*)vData Ysize:(CGSize)Ysize Usize:(CGSize)Usize Vsize:(CGSize)Vsize displayRect:(CGRect)displayRect Span:(int)spanSize;





//处理外部视频流   使用之前先把相机给停止掉   此处接收YUV数据  返回RGBA数据    如果要得到滤镜处理后的视频帧 从YfSessionCameraDelegate获取
- (void)receiveYUVTextureY:(void*)yData U:(void*)uData V:(void*)vData Ysize:(CGSize)Ysize Usize:(CGSize)Usize Vsize:(CGSize)Vsize videoSize:(CGSize)videoSize pts:(int64_t)pts;


//处理外部视频流   使用之前先把相机给停止掉   此处接收硬解数据  返回RGBA数据    如果要得到滤镜处理后的视频帧 从YfSessionCameraDelegate获取
- (void)receiveYUVTextureBuffer:(CVPixelBufferRef)pixelbuffer pts:(int64_t)pts;


- (void)cleanOuterDataSource;


//开启残影
- (void)useSoulOBE:(BOOL)useSoulOBE;

//开启灵魂出窍效果
- (void)useSoul:(BOOL)useSoul;
//抖动速率
//范围<0.0-2.0>    默认1.0
- (void)useSoulSpeed:(float)useSoulSpeed;





//重置
- (void)resetConfigure;



//录屏
- (void)PixelBufferCallBack:(PixelBufferCallBack)PixelBufferCallBack;

//停止录屏幕
- (void)stopScreenRecord;
@end
