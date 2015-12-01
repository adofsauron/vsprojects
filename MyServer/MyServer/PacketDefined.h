#ifndef _PACKETDEFINED_INCLUDE_H
#define _PACKETDEFINED_INCLUDE_H

#include "BaseType.h"

#define HEAD_SIG	0XAA
#define END_SIG		0XFF

typedef struct _Packet_head
{
	UCHAR	head_sig;
	UCHAR	packet_id;
	USHORT	packet_len;
}Packet_head;

#define HEAD_LEN	4	//sizeof(head_sig)+sizeof(packet_id)+sizeof(packet_len)

///////////////////////////////////////////////////
//
// 说明：c->client 表示与客户端的通信
//
//////////////////////////////////////////////////


#define PACKET_C_INIT_GAME		0x01	// 初始化
#define PACKET_C_JOIN_GAME		0X02	// 玩家加入游戏
#define PACKET_C_LOAD_OVER		0X03	// 玩家进入游戏内前，所e有的资源加载完毕
#define PACKET_C_STATUS			0X04	// 客户端向后端汇报当前的状态，每隔1000ms汇报一次
#define PACKET_C_KEYPAD			0X05	// 玩家触发按键
#define PACKET_C_MOUSE			0X06	// 玩家触发鼠标
#define PACKET_C_FIRE			0X07	// 玩家开火
#define PACKET_C_DEMAGE			0X08	// 玩家对其他人造成伤害
#define PACKET_C_PLAYER_DEATH	0X09	// 玩家死亡
#define PACKET_C_GAME_OVER		0X0A	// 游戏结束
#define PACKET_MAX				PACKET_C_GAME_OVER	//最大的通信数


///////////////////////////////////////////////////
//
//	说明：以下为结构体定义
//
//////////////////////////////////////////////////

typedef struct _Packet_InitGame
{
	SHORT	userID;		// 玩家的id, 注册后一直不变
	UCHAR	gameMode;	// 游戏类型
}Packet_InitGame;

typedef struct _Packet_JoinGame
{
	SHORT	userID;		// 玩家的id, 注册后一直不变
	UCHAR	gameMode;	// 游戏类型
	SHORT	playerID;	// 玩家在游戏内的标识id，只在游戏内有效
}Packet_JoinGame;

typedef struct _Packet_LoadOver
{
	SHORT	userID;		// 玩家的id, 注册后一直不变
	UCHAR	gameMode;	// 游戏类型
}Packet_LoadOver;

typedef struct _Packet_Status
{
	SHORT	playerID;	// 玩家在游戏内的标识id
	FLOAT	posX;		// 玩家的位置
	FLOAT   posY;		//
	FLOAT	posZ;		//
	FLOAT	dirX;		// 玩家的朝向
	FLOAT	dirY;		//
	FLOAT	dirZ;		// 
	FLOAT	mouseX;		// 鼠标沿X轴旋转	说明：鼠标所在的是由X轴和Z轴组成的平面空间内
	FLOAT	mouseZ;		// 鼠标沿Z轴旋转
	FLOAT	keyStatus;	// 玩家的按键状态
}Packet_Status;

typedef struct _Packet_KeyPad
{
	SHORT	playerID;	// 玩家在游戏内的标识id
	FLOAT	keyStatus;	// 玩家的按键状态
}Packet_KeyPad;

typedef struct _Packet_Mouse
{
	SHORT	playerID;	// 玩家在游戏内的标识id
	FLOAT	mouseX;		// 鼠标沿X轴旋转	说明：鼠标所在的是由X轴和Z轴组成的平面空间内
	FLOAT	mouseZ;		// 鼠标沿Z轴旋转
}Packet_Mouse;

typedef struct _Packet_Fire
{
	SHORT	playerID;	// 玩家在游戏内的标识id
	FLOAT	posX;		// 火花的位置
	FLOAT   posY;		//
	FLOAT	posZ;		//
}Packet_Fire;

typedef struct _Packet_Demage
{
	SHORT	attackerID;	// 攻击者的playerID
	SHORT	injurerID;	// 受伤害者的playerID
	FLOAT	demageVlue;	// 造成的伤害值
}Packet_Demage;

typedef struct _Packet_PlayerDeath
{
	SHORT	deathID;	// 死亡者的playerID
}Packet_PlayerDeath;

#endif //_PACKETDEFINED_INCLUDE_H