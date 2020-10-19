//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2009, 华中科技大学 Huazhong University of Science and Technology tickTick Group  （版权声明）  
/// All rights reserved.  
///   
/// @file    SerialPort.h    
/// @brief   串口通信类头文件  
/// Head file
///  
/// 本文件完成串口通信类的声明 
/// Declaration of Serial Port communication class 
///  
/// @version 1.0     
/// @author  卢俊  Jun Lu 
/// @E-mail：lujun.hust@gmail.com  
/// @date    2010/03/19  
///  
///  修订说明：  
/// instruction:
//////////////////////////////////////////////////////////////////////////  

#ifndef SERIALPORT_H_  
#define SERIALPORT_H_  

#include <Windows.h>  

/** 串口通信类
 *
 *  本类实现了对串口的基本操作
 * Basic Operation of Serial Port
 *  例如监听发到指定串口的数据、发送指定数据到串口
 * e.g. monitoring data from port, sending data to port
 */
class CSerialPort
{
public:
    CSerialPort(void);
    ~CSerialPort(void);

public:

    /** 初始化串口函数
     *
     *  @param:  UINT portNo 串口编号,默认值为1,即COM1,注意,尽量不要大于9. Serial port number, the default value is 1, that is COM1, pay attention, try not to be greater than 9
     *  @param:  UINT baud   波特率,默认为9600. Baud rate, default is 9600
     *  @param:  char parity 是否进行奇偶校验,'Y'表示需要奇偶校验,'N'表示不需要奇偶校验 Whether to perform parity check,'Y' means parity check is required,'N' means parity check is not required
     *  @param:  UINT databits 数据位的个数,默认值为8个数据位 The number of data bits, the default value is 8 data bits
     *  @param:  UINT stopsbits 停止位使用格式,默认值为1 Stop bit format, the default value is 1
     *  @param:  DWORD dwCommEvents 默认为EV_RXCHAR,即只要收发任意一个字符,则产生一个事件 The default is EV_RXCHAR, that is, as long as any character is sent and received, an event will be generated
     *  @return: bool  初始化是否成功 Whether the initialization was successful
     *  @note:   在使用其他本类提供的函数前,请先调用本函数进行串口的初始化 Before using other functions provided by this class, please call this function to initialize the serial port
     *　　　　　  \n本函数提供了一些常用的串口参数设置,若需要自行设置详细的DCB参数,可使用重载函数 This function provides some commonly used serial port parameter settings. If you need to set detailed DCB parameters yourself, you can use the overloaded function
     *           \n本串口类析构时会自动关闭串口,无需额外执行关闭串口 The serial port will be automatically closed when the serial port class is deconstructed, without additional execution of closing the serial port
     *  @see:
     */
    bool InitPort(UINT  portNo = 1, UINT  baud = CBR_9600, char  parity = 'N', UINT  databits = 8, UINT  stopsbits = 1, DWORD dwCommEvents = EV_RXCHAR);

    /** 串口初始化函数 Serial port initialization function
     *
     *  本函数提供直接根据DCB参数设置串口参数 This function provides direct setting of serial port parameters based on DCB parameters
     *  @param:  UINT portNo
     *  @param:  const LPDCB & plDCB
     *  @return: bool  初始化是否成功 Whether the initialization was successful
     *  @note:   本函数提供用户自定义地串口初始化参数 This function provides user-defined serial port initialization parameters
     *  @see:
     */
    bool InitPort(UINT  portNo, const LPDCB& plDCB);

    /** 开启监听线程 Open the listening thread
     *
     *  本监听线程完成对串口数据的监听,并将接收到的数据打印到屏幕输出 This monitoring thread completes the monitoring of the serial port data, and prints the received data to the screen for output
     *  @return: bool  操作是否成功 Whether the operation was successful
     *  @note:   当线程已经处于开启状态时,返回false. When the thread is already open, return false
     *  @see:
     */
    bool OpenListenThread();

    /** 关闭监听线程 Close the listening thread
     *
     *
     *  @return: bool  操作是否成功 Whether the operation was successful
     *  @note:   调用本函数后,监听串口的线程将会被关闭 After calling this function, the thread listening to the serial port will be closed
     *  @see:
     */
    bool CloseListenTread();

    /** 向串口写数据 Write data to the serial port
     *
     *  将缓冲区中的数据写入到串口 Write the data in the buffer to the serial port
     *  @param:  unsigned char * pData 指向需要写入串口的数据缓冲区 Point to the data buffer that needs to be written to the serial port
     *  @param:  unsigned int length 需要写入的数据长度 The length of the data to be written
     *  @return: bool  操作是否成功 Whether the operation was successful
     *  @note:   length不要大于pData所指向缓冲区的大小 length should not be greater than the size of the buffer pointed to by pData
     *  @see:
     */
    bool WriteData(unsigned char* pData, unsigned int length);

    /** 获取串口缓冲区中的字节数 Get the number of bytes in the serial buffer
     *
     *
     *  @return: UINT  操作是否成功 Whether the operation was successful
     *  @note:   当串口缓冲区中无数据时,返回0 When there is no data in the serial buffer, return 0
     *  @see:
     */
    UINT GetBytesInCOM();

    /** 读取串口接收缓冲区中一个字节的数据 Read one byte of data in the serial port receive buffer
     *
     *
     *  @param:  char & cRecved 存放读取数据的字符变量 Character variable to store read data
     *  @return: bool  读取是否成功 Whether the reading is successful
     *  @note:
     *  @see:
     */
    bool ReadChar(char& cRecved);

private:

    /** 打开串口 Open the serial port
     *
     *
     *  @param:  UINT portNo 串口设备号 Serial device number
     *  @return: bool  打开是否成功 Whether the opening is successful
     *  @note:
     *  @see:
     */
    bool openPort(UINT  portNo);

    /** 关闭串口 Close the serial port
     *
     *
     *  @return: void  操作是否成功 Whether the operation was successful
     *  @note:
     *  @see:
     */
    void ClosePort();

    /** 串口监听线程 Serial monitor thread
     *
     *  监听来自串口的数据和信息 Monitor data and information from the serial port
     *  @param:  void * pParam 线程参数 Thread parameters
     *  @return: UINT WINAPI 线程返回值 Thread return value
     *  @note:
     *  @see:
     */
    static UINT WINAPI ListenThread(void* pParam);

private:

    /** 串口句柄  Serial port handle*/
    HANDLE  m_hComm;

    /** 线程退出标志变量 Thread exit flag variable */
    static bool s_bExit;

    /** 线程句柄 Thread handle */
    volatile HANDLE    m_hListenThread;

    /** 同步互斥,临界区保护 Synchronous mutual exclusion, critical section protection */
    CRITICAL_SECTION   m_csCommunicationSync;       //!< 互斥操作串口  Mutually exclusive operation serial port

};

#endif //SERIALPORT_H_ 