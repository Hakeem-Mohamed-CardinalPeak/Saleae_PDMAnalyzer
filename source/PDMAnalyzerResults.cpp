#include "PDMAnalyzerResults.h"
#include <AnalyzerHelpers.h>
#include "PDMAnalyzer.h"
#include "PDMAnalyzerSettings.h"
#include <iostream>
#include <fstream>

PDMAnalyzerResults::PDMAnalyzerResults( PDMAnalyzer* analyzer, PDMAnalyzerSettings* settings )
:	AnalyzerResults(),
	mSettings( settings ),
	mAnalyzer( analyzer )
{
}

PDMAnalyzerResults::~PDMAnalyzerResults()
{
}

void PDMAnalyzerResults::GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base )
{
	ClearResultStrings();
	Frame frame = GetFrame( frame_index );

	char number_str1[128];
	char number_str2[128];
	AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str1, 128 );
	AnalyzerHelpers::GetNumberString(frame.mData2, display_base, 8, number_str2, 128);
	AddResultString( number_str1, ", ", number_str2 );
}

void PDMAnalyzerResults::GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id )
{
	std::ofstream file_stream( file, std::ios::out );

	U64 trigger_sample = mAnalyzer->GetTriggerSample();
	U32 sample_rate = mAnalyzer->GetSampleRate();

	file_stream << "Time [s],Left,Right" << std::endl;

	U64 num_frames = GetNumFrames();
	for( U32 i=0; i < num_frames; i++ )
	{
		Frame frame = GetFrame( i );
		
		char time_str[128];
		AnalyzerHelpers::GetTimeString( frame.mStartingSampleInclusive, trigger_sample, sample_rate, time_str, 128 );

		char number_str1[128];
		AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str1, 128 );

		char number_str2[128];
		AnalyzerHelpers::GetNumberString(frame.mData2, display_base, 8, number_str2, 128);

		file_stream << time_str << "," << number_str1 << "," << number_str2 << std::endl;

		if( UpdateExportProgressAndCheckForCancel( i, num_frames ) == true )
		{
			file_stream.close();
			return;
		}
	}

	file_stream.close();
}

void PDMAnalyzerResults::GenerateFrameTabularText( U64 frame_index, DisplayBase display_base )
{
#ifdef SUPPORTS_PROTOCOL_SEARCH
	Frame frame = GetFrame( frame_index );
	ClearTabularText();

	char number_str[128];
	AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str, 128 );
	AddTabularText( number_str );
#endif
}

void PDMAnalyzerResults::GeneratePacketTabularText( U64 packet_id, DisplayBase display_base )
{
	//not supported

}

void PDMAnalyzerResults::GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base )
{
	//not supported
}