/*
		-Written by [ Btabtab ]

	This is a utility that will handle exporting
	and saving indiviual frames that can be used
	to produce a GIF. This utility supports
	frameskip, custom folder names, and how
	many seconds to run for (provided the framerate
	is running at 60fps).

	There is currently maybe a bug / artifact with
	the code in that the first frame produced is
	always black / blank. So to get around this it
	will refuse to draw the first frame and only
	start from frame 2 and onwards.
*/

#ifndef GIFEXPORT_H
#define GIFEXPORT_H

#include <raylib.h>
#include <stdlib.h>

/*
	This is a convenient wrapper that makes passing information
	to the screenshot saver easier and more convenient.
	This is good if using a different library other than RAYLIB
	for saving screenshots of the appication.
*/
void exportScreenshot(char* folder_name, int frame_number)
{
	TakeScreenshot(FormatText("%s/%d.png", folder_name, frame_number));
}

/*
	This function will run through (for "seconds_to_run_for" * 60)
	this means that it will run for each frame for the seconds specified.
	
	This results in producing an animation of what's happening in the
	window. This means that it can be outputted to some sort of
	GIF exporter.

	Returns TRUE when finished.
	This is useful if you want to kill the window once it is finished
	rendering the output.

	The function runs through each frame, saves the frame as a
	screenshot as a file.
*/
bool gifExport(char* folder_name, int seconds_to_run_for, int frame_skip_amount, bool reset)
{
	static int frames = 0;
	static bool draw_frame = false;

	if(reset)
	{
		frames = 0;
	}

	if(!frame_skip_amount)
	{
		draw_frame = true;
	}
	else
	{
		draw_frame = !(frames % frame_skip_amount);
	}

	if(draw_frame)
	{
		/*
			This is the true amount of frames that have been rendered.
			This allows for frames drawn with frameskip to keep their
			true numbering to prevent any GIF makers possibly throwing
			a tantrum because of gaps in the order.
		*/
		static int true_frame_count = 1;
		//draw the frame if it is after the first one.
		if(frames)
		{
			exportScreenshot(folder_name, true_frame_count);
		}
		true_frame_count++;
	}

	//increment frame.
	frames++;

	/*
		Handles returning when the process is finished.
	*/
	if((seconds_to_run_for * 60) < frames)
	{
		frames = 0;
		
		return true;
	}
	return false;
}

#endif