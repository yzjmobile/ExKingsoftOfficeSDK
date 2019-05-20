//
//  KWOfficeApi.h
//  KingsoftOfficeSDK Version 1.9.2
//
//  Created by tang feng on 14-3-18.
//  Copyright (c) 2014年 KingSoft Co.,Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol KWOfficeApiDelegate <NSObject>

@required
/**
 *  wps回传文件数据回调
 *
 *  @param dict 回传文件数据
 */
- (void)KWOfficeApiDidReceiveData:(NSDictionary*)dict;

/**
 *  wps编辑完成返回 结束与WPS链接
 */
- (void)KWOfficeApiDidFinished;

/**
 *  非正常退出
 */
-(void)KWOfficeApiDidAbort;

/**
 *  断开链接
 *
 *  @param error 错误信息
 */
- (void)KWOfficeApiDidCloseWithError:(NSError*)error;

@optional

/**
 *  共享播放开启成功回调
 *
 *  @param accessCode 接入码
 *  @param serverHost 接入的主机地址
 */
- (void)KWOfficeApiStartSharePlayDidSuccessWithAccessCode:(NSString *)accessCode
                                               serverHost:(NSString *)serverHost;

/**
 *  共享播放开启失败回调
 *
 *  @param errorMessage 失败信息
 */
- (void)KWOfficeApiStartSharePlayDidFailWithErrorMessage:(NSString *)errorMessage;

/**
 *  共享播放接入成功回调
 */
- (void)KWOfficeApiJoinSharePlayDidSuccess;

/**
 *  共享播放接入失败回调
 *
 *  @param errorMessage 失败信息
 */
- (void)KWOfficeApiJoinSharePlayDidFailWithErrorMessage:(NSString *)errorMessage;

@end


@interface KWOfficeApi : NSObject

@property(nonatomic,assign)id <KWOfficeApiDelegate>delegate;

/**
 *  实例化接口
 *
 *  @return KWOfficeApi
 */
+(id)sharedInstance;

/**
 *  设置链接端口
 *
 *  @param port 端口号，默认端口：9616
 */
+ (void)setPort:(NSInteger)port;

/**
 *  设置打印日志
 *
 *  @param debugMode 是否开启
 */
+ (void)setDebugMode:(BOOL)debugMode;

/**
 *  设置后台模式
 *
 *  @param backgroundMode YES是强制后台模式，NO则是非强制后台模式
 *  @param 如果设置的是强制后台模式还需要在info.plist当中设置后台请求，详见操作手册
 */
+ (void)setBackgroundMode:(BOOL)backgroundMode;

/**
 *  设置水印
 *
 *  @param text     水印文字
 *  @param red      红色值 范围：0-255
 *  @param green    绿色值 范围：0-255
 *  @param blue     蓝色值 范围：0-255
 *  @param alpha    水印的透明度
 */
+ (void)setWatermarkText:(NSString*)text
            colorWithRed:(CGFloat)red
                   green:(CGFloat)green
                    blue:(CGFloat)blue
                   alpha:(CGFloat)alpha;

/**
 *  注册App
 *
 *  @param keyStr 企业授权序列号
 */
+(void)registerApp:(NSString *)keyStr;

/**
 *  检测是否安装了WPS
 */
+ (BOOL)isEnterpriseWPSInstalled DEPRECATED_ATTRIBUTE;
+ (BOOL)isAppstoreWPSInstalled;

/**
 *  调用AppStore去下载WPS
 */
+ (void)goDownloadWPS;

/**
 *  如果采用非后台模式即没有设置Required Background modes字段的情况下，在WPS跳转回第三方应用的时候需要调用该方法判断是否需要开启服务，如果返回值为true则需要调用resetKWOfficeApiServiceWithDelegate将服务开启
 *
 *  @param url
 *  @param sourceApplication
 *  @param annotation
 *
 *  @return 是否需要启动服务
 */
+ (BOOL)handleOpenURL:(NSURL *)url
    sourceApplication:(NSString *)sourceApplication
           annotation:(id)annotation;

/**
 *  开启服务
 *
 *  @param delegate 委托
 *
 *  @return 设置结果
 */
- (BOOL) resetKWOfficeApiServiceWithDelegate:(id)delegate;

/**
 *  setApplicationDidEnterBackground
 *
 *  @param application UIApplication
 *
 *  @return result
 */
-(BOOL)setApplicationDidEnterBackground:(UIApplication *)application;

/**
 *  跳转到WPS操作所传输的文件
 *
 *  @param data       文件数据（NSData）
 *  @param fileName   文件名
 *  @param callback   切换回第三方App的URL名(callback)
 *  @param delegate   委托
 *  @param rightsDict 操作文件权限
 *  @param errPtr     错误信息
 *
 *  @return 跳转结果
 */
-(BOOL)sendFileData:(NSData *)data
       withFileName:(NSString *)fileName
           callback:(NSString *)callback
           delegate:(id)delegate
             policy:(NSDictionary *)rightsDict
              error:(NSError **)errPtr;

/**
 *  开启共享播放
 *
 *  @param data       文件数据（NSData）
 *  @param fileName   文件名
 *  @param serverHost 第三方App提供的共享播放服务器地址(serverHost：ip:port)
 *  @param callback   切换回第三方App的URL名(callback)
 *  @param delegate   委托
 *  @param errPtr     错误信息
 *
 *  @return 开启结果
 */
- (BOOL)startSharePlay:(NSData *)data
          withFileName:(NSString *)fileName
            serverHost:(NSString *)serverHost
              callback:(NSString *)callback
              delegate:(id)delegate
                 error:(NSError **)errPtr;

/**
 *  接入共享播放
 *
 *  @param accessCode 接入码
 *  @param serverHost 第三方App提供的共享播放服务器地址(serverHost：ip:port)
 *  @param callback   切换回第三方App的URL名(callback)
 *  @param delegate   委托
 *  @param rightsDict 操作文件权限
 *  @param errPtr     错误信息
 *
 *  @return 接入结果
 */
- (BOOL)joinSharePlay:(NSString *)accessCode
           serverHost:(NSString *)serverHost
             callback:(NSString *)callback
             delegate:(id)delegate
                error:(NSError **)errPtr;

/**
 *  只使用企业版 WPS 打开文件请使用此方法，并设置 enterpriseOnly 属性为 YES
 *
 *  @param data           文件数据（NSData）
 *  @param fileName       文件名
 *  @param callback       切换回第三方App的URL名(callback)
 *  @param delegate       委托
 *  @param rightsDict     操作文件权限
 *  @param errPtr         错误信息
 *  @param enterpriseOnly
 *
 *  @return 打开结果
 */
- (BOOL)sendFileData:(NSData *)data
        withFileName:(NSString *)fileName
            callback:(NSString *)callback
            delegate:(id)delegate
              policy:(NSDictionary *)rightsDict
               error:(NSError **)errPtr
      enterpriseOnly:(BOOL)enterpriseOnly DEPRECATED_ATTRIBUTE;

@end

