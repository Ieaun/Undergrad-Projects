%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Template script to Count Starfish in any given file
% Script contains functions required to fulfill ACW for Module 600100
% Author: 
% Date: 28 January 2019
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Development and test Matlab code snippets to run specific functions
% Add functions for each part of your Image Processing Pipeline
% Add lines to run Toplevel function once loaded into Matlab

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Four top level Matlab calls for ACW demo
% Ensure these work for some ACw images prior to demo
% Process PRIMARY image
% 'C:\Users\user\Documents\MATLAB\Computer vision', 'starfish_5.jpg'
% StarfishCount('X:\MyDrive\ComputerVision\ACW\Images', 'Starfish.jpg');
% Process different Noise image - SECOND image
% Starfish_noiseN will be replaced with for example Starfish_noise5
% StarfishCount('X:\MyDrive\ComputerVision\ACW\Images', 'Starfish_noiseN.jpg');
% Process different Colour Map image - THIRD image
% Starfish_mapM will be replaced with for example Starfish_map1
% StarfishCount('X:\MyDrive\ComputerVision\ACW\Images', 'Starfish_mapM.jpg');
% Process FOURTH image
% StarfishCount('X:\MyDrive\ComputerVision\ACW\Images', 'starfish_5.jpg');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Following line is example of script that calls intermediary function
% Source = readimagefile('X:\MyDrive\ComputerVision\ACW\Images', 'Starfish.jpg');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% StarfishCount/2 - Runs Image Processing Pipeline
function StarfishCount( folder, filename)
% Template Top Level function to Count number of Starfish in given image
% Ensure All functions or code lines are fully commented
  Source = readimagefile( folder, filename); 
%if using starfish5
  Star5 = strcmp('starfish_5.jpg',filename);
  if Star5
      PipeStar5(Source);
  else
      StarfishNumber = CountinfStarsACW(Source);
  end
end % End of Top Level Matlab Function

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% readimagefile/2 Returns image
function image = readimagefile( folder, filename)
% just read file and return as image
% could have file checks
  fullfilename = fullfile(folder, filename);
  image = imread(fullfilename);
end % of readimagefile( folder, filename)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Empty function definition for returning multiple results
function [result1 result2] = DummyFunction( Arg1, Arg2, Arg3 )
end % of DummyFunction( Arg1, Arg2, Arg3 )

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%eof