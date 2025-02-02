// ============================================================================
//
//			ＤＸＡファイル作成ソフト
//
//	Creator			: 山田　巧
//	Creation Date	: 2003/09/13
//	Version			: 1.07
//
// ============================================================================

// include ----------------------------
#include "DXArchive.h"
#include "FileLib.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>

// define -----------------------------
#define VERSION			"1.07"				// バージョン
#define FILETYPE		"dxa"				// 拡張子

// code -------------------------------

// メイン関数
int main( int argc, char *argv[] )
{
	char SrcPath[256], DestPath[256], *KeyString, *SrcDirectoryPath, *DestFilePath ;
	bool Press ;
	int i ;

	printf( "ＤＸＡファイル簡易作成ソフト  Ver%s\n", VERSION ) ;

	// 引数が一個だったらヘルプを出す
	if( argc == 1 ) goto ERR ;

	Press = true ;
	SrcDirectoryPath = NULL ;
	DestFilePath = NULL ;
	KeyString = NULL ;
	for( i = 1 ; i < argc ; i ++ )
	{
		if( argv[i][0] == '-' && argv[i][1] == 'K' && argv[i][2] == ':' )
		{
			KeyString = argv[i] + 3 ;
		}
		else
		if( argv[i][0] == '-' && argv[i][1] == 'N' && argv[i][2] == 'P' && argv[i][3] == '\0' )
		{
			Press = false ;
		}
		else
		if( SrcDirectoryPath == NULL )
		{
			SrcDirectoryPath = argv[i] ;
		}
		else
		{
			DestFilePath = argv[i] ;
		}
	}

	if( SrcDirectoryPath == NULL )
		goto ERR ;

	// ソースパスのフルパスを作成する
	ConvertFullPath__( SrcDirectoryPath, SrcPath ) ;

	// 出力ファイルパスの作成
	{
		if( DestFilePath != NULL )
		{
			char temp[256] ;

			strcpy( temp, DestFilePath ) ;
			ConvertFullPath__( temp, DestPath ) ;
		}
		else
		{
			// ソースパスから出力ファイル名を作成する
			sprintf( DestPath, "%s.%s", SrcPath, FILETYPE ) ;
		}
	}

	// アーカイブファイルを作成する
	DXArchive::EncodeArchiveOneDirectory( DestPath, SrcPath, Press, KeyString ) ;

	// 終了
	return 0 ;

ERR:

	printf( "DxaEncode.exe [-K:KeyString] [-NP] SrcDirectoryPath  [DestFilePath]\n\n" ) ;
	printf( "・ＤＸＡファイルにしたいフォルダをドラッグ＆ドロップするだけでも作成可能です\n" ) ; 
	printf( "・-K  オプションで鍵を設定出来ます(最大256文字前後) 　例  -K:KeyCode \n" ) ; 
	printf( "・-NP アーカイブ時に圧縮を行わない\n" ) ;
	return -1; 
}


