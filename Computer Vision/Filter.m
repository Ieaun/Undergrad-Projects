%Method = 0 means dont use filter, Method = 1 means use median, Method = 2 mean use mean,
function FilteredImage = Filter(Method,Image)  
if Method == 0
    FilteredImage = Image; 
      %(Median)
elseif Method == 1 
    r1 = Image(:,:,1);
    g1 = Image(:,:,2);
    b1 = Image(:,:,3);  
    
    r1 = medfilt2(r1,[3 3]);
    g1 = medfilt2(g1,[3 3]);
    b1 = medfilt2(b1,[3 3]);
    
    FilteredImage(:,:,1)= r1;
    FilteredImage(:,:,2)= g1;
    FilteredImage(:,:,3)= b1;
    FilteredImage = uint8(FilteredImage);       
        
    %(Mean)     
elseif Method == 2
    r1 = Image(:,:,1);
    g1 = Image(:,:,2);
    b1 = Image(:,:,3);
    
    %use mean filter to smooth out noise 
    for p = 1:3
        switch p
            case 1
                [m,n] = size(r1);
            case 2
                [m,n] = size(g1);
            case 3
                [m,n] = size(b1);
        end
        output = zeros(m,n); 
        for i =1:n
            for j=1:n
                %neigbouthood boundries 
                rmin = max(1,i-2);
                rmax = min(m,i+2);
                cmin = max(1,j-2);
                cmax = min(n,j+2);
                %neighbourhood matrix
                if p==1
                    temp = r1(rmin:rmax,cmin:cmax); 
                elseif p ==2
                    temp = g1(rmin:rmax,cmin:cmax);
                elseif p ==3
                    temp = b1(rmin:rmax,cmin:cmax);
                end       
                %ith pixel output = average of neighbourhood
                    output(i,j)= mean(temp(:));   
            end
        end
        %convert the output to uint8
        output = uint8(output);   
        if     p==1
            RedChannel = output;
        elseif p ==2
            GreenChannel = output;
        elseif p ==3
            BlueChannel = output;
        end  
    end  
    
    FilteredImage = cat(3,RedChannel,GreenChannel,BlueChannel);    
    
end
    
end