   M S B A M L   `   `   `  ����G  CManagementUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null5clr-namespace:ManagementUI_TestManagementUI_Test  5   	        ManagementUI_Test.Schedule   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   1localclr-namespace:ManagementUI_Test     5   	     � Title$  Schedule��5   	   $��417.891��6   $��682.428��6+   .��5	      �  � ColumnDefinitions 5
   
   �� 5      $
��565* �6   �� 5      $
��109* �6   .+�5   
   �� -   5         ��Name$ PlaysListbox��5      $
��Left=�6Y   $	��281��6t   $��	21,36,0,0q�6�   $	��Top=�6�   $��91��6�   	� 5   
   -   5         	�Name$ repeatingRadionButton��5      $��	Repeating��65   $
��Left=�6I   $��
178,77,0,0q�6d   $	��Top=�6x   	� 5   
   -   5        $ mainplayRadioButton��5      $��	Main Play��63   $
��Left=�6G   $��178,110,0,0q�6b   $	��Top=�6w   �� 5   
   -   5         ��Name$ upperCirclePriceTextbox��5      $
��Left=�63   $��23��6N   $��
401,73,0,0q�6Z    �� TextWrapping$
 Wrap=�6n   $�� ��6�   $	��Top=�6�   $	��120��6�   �� 5   
   -   5        $ dressCirclePriceTextbox��5      $
��Left=�63   $��23��6N   $��401,108,0,0q�6Z   $
 Wrap=�6o   $�� ��6�   $	��Top=�6�   $	��120��6�   �� 5   
   -   5        $ stallsPriceTextbox��5      $
��Left=�6.   $��23��6I   $��401,140,0,0q�6U   $
 Wrap=�6j   $�� ��6~   $	��Top=�6�   $	��120��6�   �� 5   
   $
��Left=�6   $��
309,73,0,0q�6/   $
��Wrap=�6C   $��Upper Circle:��6W   $	��Top=�6l   $��69��6�   �� 5   
   $
��Left=�6   $��309,106,0,0q�6/   $
��Wrap=�6D   $��Dress Cirlcle:��6X   $	��Top=�6n   �� 5   
   $
��Left=�6   $��346,138,0,0q�6/   $
��Wrap=�6D   $��Stalls:��6X   $	��Top=�6g   �� 5   
   $
��Left=�6   $��
176,10,0,0q�6/   $
��Wrap=�6C   $��Add Play��6W   $	��Top=�6g   $	��140��6    �� TextAlignment$ Center=�6�   �� 5   
   $
��Left=�6   $��
401,39,0,0q�6/   $
��Wrap=�6C   $��Ticket Prices��6W   $	��Top=�6l   $	��120��6�   �� 5   
   $
��Left=�6   $��
178,42,0,0q�6/   $
��Wrap=�6C   $��Type:��6W   $	��Top=�6d   �� 5   
   $
��Left=�6   $��176,183,0,0q�6/   $
��Wrap=�6D   $��
Play Name:��6X   $	��Top=�6j   �� 5   
   $
��Left=�6   $��178,216,0,0q�6/   $
��Wrap=�6D   $��Length (h):��6X   $	��Top=�6k   $��57��6�   �� 5   
   -   5        $ playNameTextbox��5      $
��Left=�6+   $��23��6F   $��258,182,0,0q�6R   $
 Wrap=�6g   $�� ��6{   $	��Top=�6�   $	��120��6�   �� 5   
   -   5        $ playLengthTextbox��5      $
��Left=�6-   $��23��6H   $��258,215,0,0q�6T   $
 Wrap=�6i   $�� ��6}   $	��Top=�6�   $	��120��6�   �� 5   
   $
��Left=�6   $��	21,11,0,0q�6/   $
��Wrap=�6B   $��Plays��6V   $	��Top=�6c   �� 5   
   -	   5         ��Name$ deleteSelectedPlayButton��5      $��Delete Selected��63   $
��Left=�6M   $��
21,324,0,0q�6h   $	��Top=�6|   $��91��6�   6�   �� 5    
   -
   5        $ createPlayButton��5       $��Create��6+   $
��Left=�6<   $��401,216,0,0q�6W   $	��Top=�6l   $��75��6�   6�   �� 5!   
   -   5        $ 
BackButton��5!      $
��Back��6%   $
��Left=�64   $��
10,357,0,0q�6O   $	��Top=�6c   $��75��6{   6�   �� 5"   
   $
��Left=�6   $��
541,11,0,0q�6/   $
��Wrap=�6C   $��Performances��6W   $	��Top=�6k   $��2��6�   �� 5#   
   -   5        $ performanceListBox��5#      $
��Left=�6.   $	��281��6I   $��
541,36,0,0q�6V   $	��Top=�6j   $��91��6�   $��2��6�   �� 5$   
   -   5        $% deleteSelectedPerformanceButton��5$      $��Delete Selected��6:   $
��Left=�6T   $��541,324,0,0q�6o   $	��Top=�6�   $��91��6�   $��2��6�   �� 5%   
   $
��Left=�6   $��176,253,0,0q�6/   $
��Wrap=�6D   $��Add Performance��6X   $	��Top=�6o   $	��140��6�   $ Center=�6�   �� 5&   
   $
��Left=�6   $��176,298,0,0q�6/   $
��Wrap=�6D   $
��Date��6X   $	��Top=�6d   �� 5'   
   -   5        $ addDateButton��5'      $��Add Date��6(   $
��Left=�6;   $��401,296,0,0q�6V   $	��Top=�6k   $��75��6�   6�   (  "System.Windows.Controls.DatePicker  5(   
   -   5          Name$ 	dateField��5(      $
��Left=�6(   $��23��6C   $��258,294,0,0q�6O   $	��Top=�6d   $	��120��6|   5*      5+      