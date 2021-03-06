// 
//  Font data for Arial 16pt
// 
#include "hw_ssd1306.h"
struct protoFontInformation Arial24;
// Character bitmaps for Arial 16pt
const char bitmapsArial24[] = 
{
// @0 '.' (3 pixels wide)
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	//    
	// ###
	// ###
	// ###
	0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 
	0x70, 0x70, 0x70, 

	// @9 '0' (16 pixels wide)
	//      ######     
	//    ##########   
	//   ############  
	//  #####    ####  
	//  ###        ### 
	//  ###        ### 
	// ###          ###
	// ###          ###
	// ###          ###
	// ###          ###
	// ###          ###
	// ###          ###
	// ###          ###
	// ###          ###
	// ###          ###
	// ###          ###
	// ###          ###
	//  ###        ### 
	//  ###        ### 
	//  #####    ##### 
	//   ############  
	//    ##########   
	//      ######     
	0xC0, 0xF8, 0xFC, 0x3E, 0x0E, 0x0F, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x0E, 0x3E, 0xFC, 0xF0, 0xC0, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0x01, 0x0F, 0x1F, 0x3E, 0x38, 0x78, 0x70, 0x70, 0x70, 0x70, 0x78, 0x38, 0x3E, 0x1F, 0x0F, 0x01, 

	// @57 '1' (9 pixels wide)
	//        ##
	//       ###
	//      ####
	//     #####
	//   #######
	//  #### ###
	// ####  ###
	// ##    ###
	//       ###
	//       ###
	//       ###
	//       ###
	//       ###
	//       ###
	//       ###
	//       ###
	//       ###
	//       ###
	//       ###
	//       ###
	//       ###
	//       ###
	//       ###
	0xC0, 0xE0, 0x70, 0x70, 0x38, 0x1C, 0xFE, 0xFF, 0xFF, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 

	// @84 '2' (15 pixels wide)
	//     #######    
	//   ###########  
	//  ############# 
	//  ####     #### 
	// ###        ####
	// ###         ###
	//             ###
	//             ###
	//             ###
	//            ### 
	//            ### 
	//           ###  
	//          ###   
	//         ###    
	//        ###     
	//      ####      
	//     ####       
	//    ###         
	//   ###          
	//  ###           
	//  ##############
	// ###############
	// ###############
	0x30, 0x3C, 0x3E, 0x0E, 0x0F, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x1E, 0xFE, 0xFC, 0xF0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xE0, 0x70, 0x38, 0x1E, 0x0F, 0x07, 0x01, 
	0x60, 0x78, 0x7C, 0x7E, 0x77, 0x73, 0x71, 0x71, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 

	// @129 '3' (16 pixels wide)
	//      ######     
	//    ##########   
	//   ############  
	//  ####     ####  
	// ####        ### 
	// ###         ### 
	//             ### 
	//            #### 
	//           ####  
	//       #######   
	//       #######   
	//       ########  
	//            #### 
	//             ####
	//              ###
	//              ###
	//              ###
	// ###          ###
	// ####        ### 
	//  ####      #### 
	//   ############  
	//    ##########   
	//      ######     
	0x30, 0x38, 0x3C, 0x1E, 0x0E, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x8E, 0xFE, 0xFC, 0xF0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0E, 0x0E, 0x0E, 0x0F, 0x1F, 0x3F, 0xF9, 0xF0, 0xE0, 
	0x06, 0x0E, 0x1E, 0x3C, 0x38, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x38, 0x3C, 0x1F, 0x0F, 0x03, 

	// @177 '4' (16 pixels wide)
	//            ##   
	//           ###   
	//          ####   
	//         #####   
	//         #####   
	//        ######   
	//       ### ###   
	//      #### ###   
	//      ###  ###   
	//     ###   ###   
	//    ###    ###   
	//    ###    ###   
	//   ###     ###   
	//  ###      ###   
	// ###       ###   
	// ################
	// ################
	// ################
	//           ###   
	//           ###   
	//           ###   
	//           ###   
	//           ###   
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF8, 0x3C, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
	0xC0, 0xE0, 0xF0, 0xBC, 0x9E, 0x8F, 0x83, 0x81, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x7F, 0x7F, 0x7F, 0x03, 0x03, 0x03, 

	// @225 '5' (16 pixels wide)
	//   ############# 
	//   ############# 
	//   ############# 
	//  ###            
	//  ###            
	//  ###            
	//  ###            
	//  ###  #####     
	//  ## #########   
	// ##############  
	// #####      #### 
	// ###         ### 
	//              ###
	//              ###
	//              ###
	//              ###
	//              ###
	// ###          ###
	// ####        ### 
	//  ####      #### 
	//  #############  
	//    ##########   
	//     #######     
	0x00, 0xF8, 0xFF, 0xFF, 0x07, 0x07, 0x87, 0x87, 0x87, 0x87, 0x87, 0x07, 0x07, 0x07, 0x07, 0x00, 
	0x0E, 0x0F, 0x0F, 0x06, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x0F, 0xFE, 0xFC, 0xF0, 
	0x06, 0x1E, 0x1E, 0x3C, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x38, 0x3C, 0x1F, 0x0F, 0x03, 

	// @273 '6' (16 pixels wide)
	//       ######    
	//     ##########  
	//    ############ 
	//   ####     #### 
	//  ####       ####
	//  ###         ###
	//  ###            
	// ###             
	// ###   ######    
	// ### #########   
	// ##############  
	// ######     #### 
	// ####        ####
	// ###          ###
	// ###          ###
	// ###          ###
	// ###          ###
	//  ###         ###
	//  ###        ### 
	//   ####     #### 
	//   ############  
	//     #########   
	//      ######     
	0x80, 0xF0, 0xF8, 0x7C, 0x1E, 0x0E, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x1E, 0x3E, 0x3C, 0x30, 
	0xFF, 0xFF, 0xFF, 0x1C, 0x0E, 0x0E, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x1E, 0xFC, 0xF8, 0xF0, 
	0x01, 0x07, 0x1F, 0x1E, 0x38, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x38, 0x3C, 0x1F, 0x0F, 0x03, 

	// @321 '7' (15 pixels wide)
	// ###############
	// ###############
	// ###############
	//             ## 
	//            ##  
	//           ###  
	//          ###   
	//         ###    
	//         ###    
	//        ###     
	//        ###     
	//       ###      
	//       ###      
	//      ###       
	//      ###       
	//     ###        
	//     ###        
	//     ###        
	//     ###        
	//    ###         
	//    ###         
	//    ###         
	//    ###         
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x87, 0xC7, 0xE7, 0x77, 0x3F, 0x0F, 0x07, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF8, 0x7E, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x78, 0x7F, 0x7F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @366 '8' (16 pixels wide)
	//      ######     
	//    ##########   
	//   ############  
	//  ####      ###  
	//  ###        ### 
	//  ###        ### 
	//  ###        ### 
	//  ###        ### 
	//   ###      ###  
	//    ##########   
	//     ########    
	//   ############  
	//  ####      #### 
	//  ###        ### 
	// ###          ###
	// ###          ###
	// ###          ###
	// ###          ###
	// ####        ####
	//  ####      #### 
	//   ############  
	//    ##########   
	//      ######     
	0x00, 0xF8, 0xFC, 0xFE, 0x0E, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0E, 0xFE, 0xFC, 0xF0, 0x00, 
	0xC0, 0xF0, 0xF9, 0x3B, 0x1F, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x1F, 0x3B, 0xF9, 0xF0, 0xC0, 
	0x07, 0x0F, 0x1F, 0x3C, 0x38, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x38, 0x3C, 0x1F, 0x0F, 0x07, 

	// @414 '9' (16 pixels wide)
	//      ######     
	//    #########    
	//   ############  
	//  ####      ###  
	//  ###        ### 
	// ###          ## 
	// ###          ###
	// ###          ###
	// ###          ###
	// ###          ###
	// ####        ####
	//  ####      #####
	//   ##############
	//    ######### ###
	//     ######   ###
	//              ###
	//             ### 
	// ###         ### 
	// ####       #### 
	//  ####     ####  
	//  ############   
	//   ##########    
	//     ######      
	0xE0, 0xF8, 0xFC, 0x1E, 0x0E, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0E, 0x1C, 0xFC, 0xF0, 0xC0, 
	0x07, 0x0F, 0x1F, 0x3C, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x30, 0x38, 0x1C, 0xFF, 0xFF, 0xFF, 
	0x06, 0x1E, 0x3E, 0x3C, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x38, 0x3C, 0x1F, 0x0F, 0x07, 0x00,

};

// Character descriptors for Arial 16pt
// { [Char width in bits], [Offset into arial_16ptCharBitmaps in bytes] }
const struct protoFontDescriptors descriptors24  [] = 
{
	{3, 0}, 		// . 
	{0, 0}, 		// / 
	{16, 9}, 		// 0 
	{9, 57}, 		// 1 
	{15, 84}, 		// 2 
	{16, 129}, 		// 3 
	{16, 177}, 		// 4 
	{16, 225}, 		// 5 
	{16, 273}, 		// 6 
	{15, 321}, 		// 7 
	{16, 366}, 		// 8 
	{16, 414}, 		// 9 


};

// Font information for Arial 16pt
struct protoFontInformation  *Arial24Init()	{
	Arial24.firstCharCode = '.';
	Arial24.lastCharCode	=	'9';
	Arial24.height = 25;
	Arial24.addrFontDataStart = bitmapsArial24;
	Arial24.addrFontDescriptor = descriptors24;
	return &Arial24;
}
