//
//  XXManager.h
//  YfSessionCamera
//
//  Created by 张涛 on 2017/5/11.
//  Copyright © 2017年 YunFan. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, YfFilterType)
{
    YfFilterNature = 0,
    YfFilterDelta,
    YfFilterElectric,
    YfFilterSlowlived,
    YfFilterTokyo,
    YfFilterWarm,
};

@interface XXManager : NSObject

//是否使用faceu功能 default is no
@property (nonatomic,assign)BOOL open;

//传入心形手势文件名
@property (nonatomic, copy) NSString *heartName;
//开启人脸追踪
@property (nonatomic, assign)BOOL is_facing_tracking;
//开启心形手势
@property (nonatomic, assign) BOOL is_heartGesture;

//滤镜选项
@property (nonatomic, assign) YfFilterType filterLever;

//磨皮等级  （0-1） 推荐 1
@property (nonatomic, assign) float beautyLever;
//美白等级  推荐 0.1
@property (nonatomic, assign) float colorLever;

//大眼 推荐  0.4
@property (nonatomic, assign) float eyeEnlarging;
//瘦脸 推荐  0.2
@property (nonatomic, assign) float cheekThinning;
//只启用美颜
@property (nonatomic, assign) BOOL isOnlyBeauty;


//传入全资源路径加载贴图
- (void)reLoadItem:(NSString *)fileName;
//传入全资源路径加载心形手势
- (void)reLoadHeartGes:(NSString *)fileName;


+ (instancetype) sharedManager;

- (CVPixelBufferRef)renderPixelbuffer:(CVPixelBufferRef)pixelbuffer;

- (void)Deleteitems;
@end
