   M S B A M L   `   `   `  ����G  CManagementUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null5clr-namespace:ManagementUI_TestManagementUI_Test  5   	   $    ManagementUI_Test.ViewBookings   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   1localclr-namespace:ManagementUI_Test     5   	     � Title$  View Bookings��5   	   $	��350��6   $��700         ��6,   .��5
      �  � ColumnDefinitions 5   
   �� 5      $	��61* �6   �� 5      $
��631* �6   .+�5   
   �� -   5        $
��Back��5      $
��Left=�6    $��25��6;   $��
10,284,0,0q�6G   $	��Top=�6[   $��56��6s   $��2��6�   �� 5   
   -   5         ��Name$ BookingsListBox��5      $
��Left=�6+   $	��204��6F   $��	21,39,0,0q�6S   $	��Top=�6f   $	��648��6~   $��2��6�   �� 5   
   -   5        $��Make Booking��5      $
��Left=�6(   $��25��6C   $��510,257,0,0q�6O   $	��Top=�6d   $��87��6|   $��1��6�   �� 5   
   -   5        $��Delete Booking��5      $
��Left=�6*   $��25��6E   $��402,257,0,0q�6Q   $	��Top=�6f   $��87��6~   $��1��6�   �� 5   
   $��2��6   $��
Booking ID��6$   $
��Left=�69   $��29��6T   $��	21,10,0,0q�6`   $	��Top=�6s   $��68��6�   �� 5   
   $��Performance ID��6   $��Right=�6)   $��29��6E   $��
0,10,479,0q�6Q   $	��Top=�6e   $��92��6}   $��1��6�   �� 5   
   $��Customer ID��6   $��Right=�6&   $��29��6B   $��
0,10,373,0q�6N   $	��Top=�6b   $��82��6z   $��1��6�    J� RenderTransformOrigin$ 0.804,0.414&�6�   �� 5   
   $
��Date��6   $��Right=�6   $��29��6;   $��
0,10,273,0q�6G   $	��Top=�6[   $��38��6s   $��1��6~   $ 0.804,0.414&�6�   �� 5   
   $��
Price (£)��6   $��Right=�6$   $��29��6@   $��	0,10,56,0q�6L   $	��Top=�6_   $��85��6w   $��1��6�   $ 0.804,0.414&�6�   5      5      