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
// ˵����c->client ��ʾ��ͻ��˵�ͨ��
//
//////////////////////////////////////////////////


#define PACKET_C_INIT_GAME		0x01	// ��ʼ��
#define PACKET_C_JOIN_GAME		0X02	// ��Ҽ�����Ϸ
#define PACKET_C_LOAD_OVER		0X03	// ��ҽ�����Ϸ��ǰ����e�е���Դ�������
#define PACKET_C_STATUS			0X04	// �ͻ������˻㱨��ǰ��״̬��ÿ��1000ms�㱨һ��
#define PACKET_C_KEYPAD			0X05	// ��Ҵ�������
#define PACKET_C_MOUSE			0X06	// ��Ҵ������
#define PACKET_C_FIRE			0X07	// ��ҿ���
#define PACKET_C_DEMAGE			0X08	// ��Ҷ�����������˺�
#define PACKET_C_PLAYER_DEATH	0X09	// �������
#define PACKET_C_GAME_OVER		0X0A	// ��Ϸ����
#define PACKET_MAX				PACKET_C_GAME_OVER	//����ͨ����


///////////////////////////////////////////////////
//
//	˵��������Ϊ�ṹ�嶨��
//
//////////////////////////////////////////////////

typedef struct _Packet_InitGame
{
	SHORT	userID;		// ��ҵ�id, ע���һֱ����
	UCHAR	gameMode;	// ��Ϸ����
}Packet_InitGame;

typedef struct _Packet_JoinGame
{
	SHORT	userID;		// ��ҵ�id, ע���һֱ����
	UCHAR	gameMode;	// ��Ϸ����
	SHORT	playerID;	// �������Ϸ�ڵı�ʶid��ֻ����Ϸ����Ч
}Packet_JoinGame;

typedef struct _Packet_LoadOver
{
	SHORT	userID;		// ��ҵ�id, ע���һֱ����
	UCHAR	gameMode;	// ��Ϸ����
}Packet_LoadOver;

typedef struct _Packet_Status
{
	SHORT	playerID;	// �������Ϸ�ڵı�ʶid
	FLOAT	posX;		// ��ҵ�λ��
	FLOAT   posY;		//
	FLOAT	posZ;		//
	FLOAT	dirX;		// ��ҵĳ���
	FLOAT	dirY;		//
	FLOAT	dirZ;		// 
	FLOAT	mouseX;		// �����X����ת	˵����������ڵ�����X���Z����ɵ�ƽ��ռ���
	FLOAT	mouseZ;		// �����Z����ת
	FLOAT	keyStatus;	// ��ҵİ���״̬
}Packet_Status;

typedef struct _Packet_KeyPad
{
	SHORT	playerID;	// �������Ϸ�ڵı�ʶid
	FLOAT	keyStatus;	// ��ҵİ���״̬
}Packet_KeyPad;

typedef struct _Packet_Mouse
{
	SHORT	playerID;	// �������Ϸ�ڵı�ʶid
	FLOAT	mouseX;		// �����X����ת	˵����������ڵ�����X���Z����ɵ�ƽ��ռ���
	FLOAT	mouseZ;		// �����Z����ת
}Packet_Mouse;

typedef struct _Packet_Fire
{
	SHORT	playerID;	// �������Ϸ�ڵı�ʶid
	FLOAT	posX;		// �𻨵�λ��
	FLOAT   posY;		//
	FLOAT	posZ;		//
}Packet_Fire;

typedef struct _Packet_Demage
{
	SHORT	attackerID;	// �����ߵ�playerID
	SHORT	injurerID;	// ���˺��ߵ�playerID
	FLOAT	demageVlue;	// ��ɵ��˺�ֵ
}Packet_Demage;

typedef struct _Packet_PlayerDeath
{
	SHORT	deathID;	// �����ߵ�playerID
}Packet_PlayerDeath;

#endif //_PACKETDEFINED_INCLUDE_H