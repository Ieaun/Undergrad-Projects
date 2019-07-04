function ThreshImage = ColourThresholder(Method,Image)  
RGB = Image;

if Method == 0
    ThreshImage = RGB;

elseif Method == 1
    % Convert RGB image to chosen color space
    I = RGB;
    % Define thresholds for channel 1 based on histogram settings
    channel1Min = 224.000;
    channel1Max = 255.000;
    % Define thresholds for channel 2 based on histogram settings
    channel2Min = 162.000;
    channel2Max = 216.000;
    % Define thresholds for channel 3 based on histogram settings
    channel3Min = 30.000;
    channel3Max = 178.000;
   % Create mask based on chosen histogram thresholds
    sliderBW = (I(:,:,1) >= channel1Min ) & (I(:,:,1) <= channel1Max) & ...
    (I(:,:,2) >= channel2Min ) & (I(:,:,2) <= channel2Max) & ...
    (I(:,:,3) >= channel3Min ) & (I(:,:,3) <= channel3Max);
    BW = sliderBW;
    % Initialize output masked image based on input image.
    maskedRGBImage = RGB;
    % Set background pixels where BW is false to zero.
    maskedRGBImage(repmat(~BW,[1 1 3])) = 0;
    ThreshImage = maskedRGBImage; 
    
elseif Method == 2
    % Convert RGB image to chosen color space
    I = RGB;
    % Define thresholds for channel 1 based on histogram settings
    channel1Min = 204.000;
    channel1Max = 255.000;
    % Define thresholds for channel 2 based on histogram settings
    channel2Min = 155.000;
    channel2Max = 230.000;
    % Define thresholds for channel 3 based on histogram settings
    channel3Min = 2.000;
    channel3Max = 185.000;
    % Create mask based on chosen histogram thresholds
    sliderBW = (I(:,:,1) >= channel1Min ) & (I(:,:,1) <= channel1Max) & ...
        (I(:,:,2) >= channel2Min ) & (I(:,:,2) <= channel2Max) & ...
        (I(:,:,3) >= channel3Min ) & (I(:,:,3) <= channel3Max);
    BW = sliderBW;
    % Initialize output masked image based on input image.
    maskedRGBImage = RGB;
    % Set background pixels where BW is false to zero.
    maskedRGBImage(repmat(~BW,[1 1 3])) = 0;
    ThreshImage = maskedRGBImage;
    
elseif Method == 3
    % Convert RGB image to chosen color space
    I = RGB;

    % Define thresholds for channel 1 based on histogram settings
    channel1Min = 213.000;
    channel1Max = 255.000;

    % Define thresholds for channel 2 based on histogram settings
    channel2Min = 0.000;
    channel2Max = 182.000;

    % Define thresholds for channel 3 based on histogram settings
    channel3Min = 0.000;
    channel3Max = 198.000;

    % Create mask based on chosen histogram thresholds
    sliderBW = (I(:,:,1) >= channel1Min ) & (I(:,:,1) <= channel1Max) & ...
    (I(:,:,2) >= channel2Min ) & (I(:,:,2) <= channel2Max) & ...
    (I(:,:,3) >= channel3Min ) & (I(:,:,3) <= channel3Max);
    BW = sliderBW;

    % Initialize output masked image based on input image.
    maskedRGBImage = RGB;

    % Set background pixels where BW is false to zero.
    maskedRGBImage(repmat(~BW,[1 1 3])) = 0;
    ThreshImage = maskedRGBImage; 
    

elseif Method == 4
          
    % Convert RGB image to chosen color space
    I = RGB;
    % Define thresholds for channel 1 based on histogram settings
    channel1Min = 211.000;
    channel1Max = 255.000;
    % Define thresholds for channel 2 based on histogram settings
    channel2Min = 0.000;
    channel2Max = 215.000;
    % Define thresholds for channel 3 based on histogram settings
    channel3Min = 7.000;
    channel3Max = 164.000;
    % Create mask based on chosen histogram thresholds
    sliderBW = (I(:,:,1) >= channel1Min ) & (I(:,:,1) <= channel1Max) & ...
        (I(:,:,2) >= channel2Min ) & (I(:,:,2) <= channel2Max) & ...
        (I(:,:,3) >= channel3Min ) & (I(:,:,3) <= channel3Max);
    BW = sliderBW;
    % Initialize output masked image based on input image.
    maskedRGBImage = RGB;
    % Set background pixels where BW is false to zero.
    maskedRGBImage(repmat(~BW,[1 1 3])) = 0;
    ThreshImage = maskedRGBImage;   

elseif Method == 5
    HSV= rgb2hsv(RGB);
    satchannel = HSV(:,:,2);
    SatFish = cat(3,satchannel,satchannel,satchannel);
    SatFIshbw = im2bw(SatFish);
    ThreshImage = SatFish; 
 
end
end