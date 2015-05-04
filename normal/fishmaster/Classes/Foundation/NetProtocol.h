//
//  NetProtocol.h
//  barracat-iphone
//
//  
//
//

#ifndef barracat_iphone_NetProtocol_h
#define barracat_iphone_NetProtocol_h

//心跳
#define MDM_GP_HeartBeat				0	//心跳
#define SUB_GP_HeartBeat				1	//心跳

//登陆错误标识

#define ERC_GP_LOGON_SUCCESS			0								//登陆成功
#define ERC_GP_ACCOUNTS_NOT_EXIST		1								//帐号不存在
#define ERC_GP_LONG_NULLITY				2								//禁止登陆
#define ERC_GP_PASSWORD_ERCOR			3								//密码错误

//////////////////////////////////////////////////////////////////////////
//登陆命令码

#define MDM_GP_LOGON					1	//广场登陆

#define SUB_GP_LOGON_ACCOUNTS			1	//帐号登陆
#define SUB_GP_LOGON_USERID				2	//I D 登陆
#define SUB_GP_REGISTER_ACCOUNTS		3		//注册帐号
#define SUB_GP_GET_PASSWORD				4	//找回密码
#define SUB_GP_CHONGZHI					5	//充值
#define SUB_GP_ZHUANZHANG				6	//转帐
#define SUB_GP_SAFEBOXPASS				7	//保险箱密码
#define SUB_GP_LOCKLOCAL				8	//本机绑定
#define SUB_GP_BUYMEMBER				9	//购买会员
#define SUB_GP_ZHUANZHANG_ID			10	//ID转帐
#define SUB_GP_SHORTMSG					11	//短信支持
#define SUB_GP_PROPD					12	//密码保护
#define SUB_GP_RESETPD					13	//密码修改
#define SUB_GP_ACCESSSCOREBANK          27	//存取分数
#define SUB_GP_WHISPER                  30  //私信

#define SUB_GP_LOGON_SUCCESS			100	//登陆成功
#define SUB_GP_LOGON_ERROR				101	//登陆失败
#define SUB_GP_LOGON_FINISH				102	//登陆完成
#define SUB_GP_SET_PWD					104	//设置密码返回
#define SUB_GP_CHONGZHI_R				105	//充值返回
#define SUB_GP_ZHUANZHANG_R				106	//转帐返回
#define SUB_GP_SAFEBOXPASS_R			107	//
#define SUB_GP_LOCKLOCAL_R				108	//
#define SUB_GP_BUYMEMBER_R				109	//
#define SUB_GP_ZHUANZHANG_ID_R			110	//ID转帐返回
#define SUB_GP_SHORTMSG_R				111	//短信发送返回
#define SUB_GP_PROPD_R					112	//保护密码返回
#define SUB_GP_RESETOD_R				113	//重设密码返回


//长度宏定义
#define ID_LEN						10		//ID长度
#define NAME_LEN						32		//名字长度
#define PASS_LEN						33		//密码长度
#define NAME_MIN_LEN					14		//名字长度--注册时限制
#define PASS_MIN_LEN					12		//密码长度--注册是限制
#define GROUP_LEN						32		//社团长度
#define E_MAIL_LEN						30		//
#define QQ_LEN						13		//QQ好
#define README_LEN						200		//个人说明
#define ADRR_ELN						20		//地址
#define WORK_LEN						30		//职业
#define XUEXING_LEN					6		//血型
#define XINGZUO_LEN					8		//星座
#define XUELI_LEN						6		//学历
#define SHENGGAO_LEN					3		//身高
#define NIANLING_LEN					3		//年龄
#define DAAN_LEN						20		//答案
#define WENTI_LEN						20
#define XINGBIE						2		    //性别

#define TITLE_LEN                       32      //商品标题
#define VICE_TITLE_LEN                  64      //商品副标题
#define DESC_LEN                        256     //商品描述

//////////////////////////////////////////////////////////////////////////
//游戏列表命令码

#define MDM_GP_SERVER_LIST				2		//列表信息

#define SUB_GP_LIST_TYPE				100		//类型列表
#define SUB_GP_LIST_KIND				101		//种类列表
#define SUB_GP_LIST_STATION				102		//站点列表
#define SUB_GP_LIST_SERVER				103		//房间列表
#define SUB_GP_LIST_FINISH				104		//发送完成
#define SUB_GP_LIST_CONFIG				105		//列表配置

#define SUB_GP_LIST_PROCESS				106		//进程列表


//长度宏定义
#define TYPE_LEN						32		//种类长度
#define KIND_LEN						32		//类型长度
#define STATION_LEN						32		//站点长度
#define SERVER_LEN						32		//房间长度
#define MODULE_LEN						32		//进程长度
#define MAX_ITEM_NUM                    12


//////////////////////////////////////////////////////////////////////////
//登陆数据包定义

#define MDM_GR_LOGON				1		//房间登陆

#define SUB_GR_LOGON_ACCOUNTS		1		//帐户登陆
#define SUB_GR_LOGON_USERID			2		//I D 登陆

#define  SUB_GP_GET_PRODUCT_INFO    35      //获取商品列表

#define SUB_GR_LOGON_SUCCESS		100		//登陆成功
#define SUB_GR_LOGON_ERROR			101		//登陆失败
#define SUB_GR_LOGON_FINISH			102		//登陆完成
#define SUB_GR_EXIT_ROOM			103		//退出房间
#define SUB_GR_EXIT_GAME			104		//退出游戏<并不退出房间>
#define SUB_GR_NEED_AUTO			105		//要求自动排队


//////////////////////////////////////////////////////////////////////////
//用户数据包定义

#define MDM_GR_USER				2		//用户信息

#define SUB_GR_USER_LOOKON_REQ		2		//旁观请求
#define SUB_GR_USER_STANDUP_REQ		3		//起立请求
#define SUB_GR_USER_LEFT_GAME_REQ	4		//离开游戏
#define SUB_GR_USER_STANDUP_AUTO_REQ	5

#define SUB_GR_USER_COME			100		//用户进入
#define SUB_GR_USER_STATUS			101		//用户状态
#define SUB_GR_USER_SCORE			102		//用户分数
#define SUB_GR_SEND_GOLD			104
#define SUB_GR_REFLUSH_GOLD			105 		//发送刷新点数
#define SUB_GR_INTO_READY_QUEUE		106		//用户进入等待队列	在防作弊房间里面用到!
#define SUB_GR_AUTO_SIT				107

#define SUB_GR_USER_CHAT			200		//聊天消息
#define SUB_GR_USER_WHISPER			201		//私语消息
#define SUB_GR_USER_RULE			202		//用户规则

#define SUB_GR_USER_INVITE			300		//邀请消息
#define SUB_GR_USER_INVITE_REQ		301		//邀请请求
#define SUB_GR_PRESENT				302		//赠送币
#define SUB_GR_PLAYPRESENT			303		//10分钟赠送
//#define SUB_GR_LOOKONPRESENT		304		//旁观分钟赠送

//////////////////////////////////////////////////////////////////////////
//配置信息数据包

#define MDM_GR_INFO				3		//配置信息

#define SUB_GR_SERVER_INFO			100		//房间配置
#define SUB_GR_ORDER_INFO			101		//等级配置
#define SUB_GR_MEMBER_INFO			102		//会员配置
#define SUB_GR_COLUMN_INFO			103		//列表配置
#define SUB_GR_CONFIG_FINISH		104		//配置完成

//////////////////////////////////////////////////////////////////////////
//房间状态数据包

#define MDM_GR_STATUS				4	//状态信息

#define SUB_GR_TABLE_INFO			100	//桌子信息
#define SUB_GR_TABLE_STATUS			101	//桌子状态
#define SUB_GR_TABLE_PASS			102	//桌子密码
#define SUB_GR_TABLE_START			103	//在自动配对模式下通知客户端是不是要显示桌子上的人了!


//////////////////////////////////////////////////////////////////////////
//游戏数据报 宏定义
//游戏状态
#define GAME_STATE_FREE              GS_FREE               //等待开始
#define GAME_STATE_YAZHU			GS_FREE+1             //接收押注
#define GAME_STATE_JIESUAN			GS_FREE+2			  //结算等待


//游戏子命令
// #define SUB_S_GAME_YAZHU            100     //押注报文，客户端发送给服务器
// #define SUB_S_GAME_START            101     //新的一轮押注开始
// #define SUB_S_GAME_YAZHUINFO        102     //通告押注情况
// #define SUB_S_GAME_DEALPOKER	    110		//发牌以及结算报文，服务器发送给客户端

#define ZHUANG_WIN 1
#define XIAN_WIN   2
#define TIE_WIN    3

#define MDM_GF_GAME						100								//”Œœ∑œ˚œ¢
#define MDM_GF_FRAME					101								//øÚº‹œ˚œ¢

#define MDM_GF_TOOLS					102								//µ¿æﬂ

#define SUB_GF_INFO						1								//”Œœ∑–≈œ¢
#define SUB_GF_USER_READY				2								//”√ªßÕ¨“‚

#define SUB_GF_OPTION					100								//”Œœ∑≈‰÷√
#define SUB_GF_SCENE					101								//≥°æ∞–≈œ¢

#define SUB_GF_USER_CHAT

//用户状态定义
#define US_NULL							0x00								//没有状态
#define US_FREE							0x01								//站立状态
#define US_SIT							0x02								//坐下状态
#define US_READY						0x03								//同意状态
#define US_LOOKON						0x04								//旁观状态
#define US_PLAY							0x05								//游戏状态
#define US_OFFLINE						0x06								//断线状态
#define US_AUTO							0x07								//自动排队

//在线人数
#define MDM_GR_SERVER_INFO			11									//∑øº‰–≈œ¢
#define SUB_GR_ONLINE_COUNT_INFO	100


//客户端校验
#define MDM_KN_COMMAND					0		//内核命令
#define SUB_KN_DETECT_SOCKET			1		//检测命令
#define SUB_KN_VERIFY_KEY				2		//客户端校验

// 游戏命令码
#define MDM_GF_GAME					100
#define SUB_S_GAME_START            100     //开始
#define SUB_S_GAME_YAZHU            101     //押注
#define SUB_S_GAME_APPLYDEALER      102     //申请当庄
#define SUB_S_GAME_YAZHURET         200     //押注返回
#define SUB_S_GAME_APPLYDEALERRET   201     //申请当庄返回
#define SUB_S_GAME_DEALPOKER		202		//发牌以及结算报文
#define SUB_S_GAME_YAZHUNOTICE      203     //押注信息通告
#define SUB_S_GAME_DEALERLISTNOTICE 204     //当庄队列通告
#define SUB_S_GAME_SCOREDIFF		205		//分数变化通告
#define SUB_S_GAME_LUDAN            206     //路单通告

#define MDM_GF_FRAME					101
#define SUB_GF_MESSAGE					300

#define SMT_INFO						0x0001							//信息消息
#define SMT_EJECT						0x0002							//弹出消息
#define SMT_GLOBAL						0x0004							//全局消息
#define SMT_CLOSE_GAME					0x1000							//关闭游戏

#endif
