using Microsoft.Win32;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO.Ports;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using UnityEngine;
using UnityEngine.XR;

/*Pose head = new();
Pose spine = new();
Pose thigh_l = new();
Pose thigh_r = new();
Pose calf_l = new();
Pose calf_r = new();
Pose upperarm_l = new();
Pose upperarm_r = new();
Pose lowerarm_l = new();
Pose lowerarm_r = new();*/


public class PortManager : MonoBehaviour
{
    private SerialPort sp;

    public Transform headTransform;
    public Transform spineTransform;
    public Transform thigh_lTransform;
    public Transform thigh_rTransform;
    public Transform calf_lTransform;
    public Transform calf_rTransform;
    public Transform upperarm_lTransform;
    public Transform upperarm_rTransform;
    public Transform lowerarm_lTransform;
    public Transform lowerarm_rTransform;

    //public AnotherScript anotherScript;

    //Transform transform = anotherScript.cubeTransform;

    class Pose
    {
        public int X { get; set; }
        public int Y { get; set; }
        public int Z { get; set; }
    }





    #region 扫描端口
    //使用API扫描
    public string[] ScanPorts_API()
    {
        string[] portList = SerialPort.GetPortNames();
        return portList;
    }
    //使用注册表信息扫描
    public string[] ScanPorts_Regedit()
    {
        RegistryKey keyCom = Registry.LocalMachine.OpenSubKey("Hardware\\DeviceMap\\SerialComm");
        string[] SubKeys = keyCom.GetValueNames();
        string[] portList = new string[SubKeys.Length];
        for (int i = 0; i < SubKeys.Length; i++)
        {
            portList[i] = (string)keyCom.GetValue(SubKeys[i]);
        }
        return portList;
    }
    //试错方式扫描
    public string[] ScanPorts_TryFail()
    {
        List<string> tempPost = new List<string>();
        bool mark = false;
        for (int i = 0; i < 10; i++)
        {
            try
            {
                SerialPort sp = new SerialPort("COM" + (i + 1).ToString());
                sp.Open();
                sp.Close();
                tempPost.Add("COM" + (i + 1).ToString());
                mark = true;
            }
            catch (System.Exception)
            {
                continue;
            }

        }
        if (mark)
        {
            string[] portList = tempPost.ToArray();
            return portList;
        }
        else
        {
            return null;
        }
    }
    #endregion

    #region 打开串口/关闭串口
    /// <summary>
    /// 打开串口
    /// </summary>
    /// <param name="COM9">端口号</param>
    /// <param name="_baudRate">波特率</param>
    /// <param name="_parity">校验位</param>
    /// <param name="dataBits">数据位</param>
    /// <param name="_stopbits">停止位</param>
    public void OpenSerialPort(string _portName, int _baudRate, Parity _parity, int dataBits, StopBits _stopbits)
    {
        try
        {
            sp = new SerialPort(_portName, _baudRate, _parity, dataBits, _stopbits);//绑定端口
            sp.Open();
            //使用委托
            //sp.DataReceived += DataReceived;
            //使用线程
            Thread thread = new Thread(new ThreadStart(DataReceived));
            thread.Start();
        }
        catch (Exception ex)
        {
            sp = new SerialPort();
            Debug.Log(ex);
        }
    }

    /// <summary>
    /// 关闭串口
    /// </summary>
    public void CloseSerialPort()
    {
        sp.Close();
    }
    #endregion

    #region 发送数据
    /// <summary>
    /// 发送数据
    /// </summary>
    /// <param name="_info">string数据</param>
    public void SendData(string _info)
    {
        try
        {
            if (sp.IsOpen)
            {
                sp.WriteLine(_info);
            }
            else
            {
                sp.Open();
                sp.WriteLine(_info);
            }
        }
        catch (Exception ex)
        {
            Debug.Log(ex);
        }
    }
    /// <summary>
    /// 发送数据
    /// </summary>
    /// <param name="send">byte数据</param>
    /// <param name="offSet">起始位</param>
    /// <param name="count">byte长度</param>
    public void SendData(byte[] send, int offSet, int count)
    {
        try
        {
            if (sp.IsOpen)
            {
                sp.Write(send, offSet, count);
            }
            else
            {
                sp.Open();
                sp.Write(send, offSet, count);
            }
        }
        catch (Exception ex)
        {
            Debug.Log(ex);
        }
    }
    #endregion

    #region 接收数据
    /// <summary>
    /// 接收数据 回调函数
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    public void DataReceived(object sender, SerialDataReceivedEventArgs e)
    {
        byte[] ReDatas = new byte[sp.BytesToRead];
        sp.Read(ReDatas, 0, ReDatas.Length);//读取数据
        DataProcessing(ReDatas);//数据处理
    }
    /// <summary>
    /// 接收数据 线程
    /// </summary>
    public void DataReceived()
    {
        while (true)
        {
            if (sp.IsOpen)
            {
                int count = sp.BytesToRead;
                if (count > 0)
                {
                    byte[] readBuffer = new byte[count];
                    try
                    {
                        sp.Read(readBuffer, 0, count);
                        DataProcessing(readBuffer);//数据处理
                        //cubeTransform.localRotation = Quaternion.Euler((float)x, (float)y, (float)z);
                    }
                    catch (Exception ex)
                    {
                        Debug.Log(ex.Message);
                    }
                }
            }
            Thread.Sleep(200);
        }

    }
    /// <summary>
    /// 数据处理
    /// </summary>
    /// <param name="data">字节数组</param>
    public void DataProcessing(byte[] data)
    {
        Pose head = new();
        Pose spine = new();
        Pose thigh_l = new();
        Pose thigh_r = new();
        Pose calf_l = new();
        Pose calf_r = new();
        Pose upperarm_l = new();
        Pose upperarm_r = new();
        Pose lowerarm_l = new();
        Pose lowerarm_r = new();



        string input = System.Text.Encoding.UTF8.GetString(data);
        MatchCollection matches = Regex.Matches(input, @"-?\d+");
        //Debug.Log(input);
        // 使用迭代索引来访问匹配结果，并将坐标赋值给对应的骨骼对象的属性
        int index = 0;

        head.X = int.Parse(matches[index++].Value);
        head.Y = int.Parse(matches[index++].Value);
        head.Z = int.Parse(matches[index++].Value);

        spine.X = int.Parse(matches[index++].Value);
        spine.Y = int.Parse(matches[index++].Value);
        spine.Z = int.Parse(matches[index++].Value);

        thigh_l.X = int.Parse(matches[index++].Value);
        thigh_l.Y = int.Parse(matches[index++].Value);
        thigh_l.Z = int.Parse(matches[index++].Value);

        thigh_r.X = int.Parse(matches[index++].Value);
        thigh_r.Y = int.Parse(matches[index++].Value);
        thigh_r.Z = int.Parse(matches[index++].Value);

        calf_l.X = int.Parse(matches[index++].Value);
        calf_l.Y = int.Parse(matches[index++].Value);
        calf_l.Z = int.Parse(matches[index++].Value);

        calf_r.X = int.Parse(matches[index++].Value);
        calf_r.Y = int.Parse(matches[index++].Value);
        calf_r.Z = int.Parse(matches[index++].Value);

        upperarm_l.X = int.Parse(matches[index++].Value);
        upperarm_l.Y = int.Parse(matches[index++].Value);
        upperarm_l.Z = int.Parse(matches[index++].Value);

        upperarm_r.X = int.Parse(matches[index++].Value);
        upperarm_r.Y = int.Parse(matches[index++].Value);
        upperarm_r.Z = int.Parse(matches[index++].Value);

        lowerarm_l.X = int.Parse(matches[index++].Value);
        lowerarm_l.Y = int.Parse(matches[index++].Value);
        lowerarm_l.Z = int.Parse(matches[index++].Value);

        lowerarm_r.X = int.Parse(matches[index++].Value);
        lowerarm_r.Y = int.Parse(matches[index++].Value);
        lowerarm_r.Z = int.Parse(matches[index++].Value);

        // 输出骨骼对象的坐标
        Debug.Log("Head: " + head.X + ", " + head.Y + ", " + head.Z);
        Debug.Log("Spine: " + spine.X + ", " + spine.Y + ", " + spine.Z);
        Debug.Log("Thigh Left: " + thigh_l.X + ", " + thigh_l.Y + ", " + thigh_l.Z);
        Debug.Log("Thigh Right: " + thigh_r.X + ", " + thigh_r.Y + ", " + thigh_r.Z);
        Debug.Log("Calf Left: " + calf_l.X + ", " + calf_l.Y + ", " + calf_l.Z);
        Debug.Log("Calf Right: " + calf_r.X + ", " + calf_r.Y + ", " + calf_r.Z);
        Debug.Log("Upper Arm Left: " + upperarm_l.X + ", " + upperarm_l.Y + ", " + upperarm_l.Z);
        Debug.Log("Upper Arm Right: " + upperarm_r.X + ", " + upperarm_r.Y + ", " + upperarm_r.Z);
        Debug.Log("Lower Arm Left: " + lowerarm_l.X + ", " + lowerarm_l.Y + ", " + lowerarm_l.Z);
        Debug.Log("Lower Arm Right: " + lowerarm_r.X + ", " + lowerarm_r.Y + ", " + lowerarm_r.Z);

        /*string pattern = @"x:(-?\d+),y:(-?\d+),z:(-?\d+)";
        Match match = Regex.Match(str, pattern);

        if (match.Success)
        {
             x = int.Parse(match.Groups[1].Value);
             y = int.Parse(match.Groups[2].Value);
             z = int.Parse(match.Groups[3].Value);




            // 使用 x, y, z 的值做一些处理
            Debug.Log($"x:{x}, y:{y}, z:{z}");
        }
        else
        {
            Debug.Log("字符串中没有符合格式要求的子串");
        }*/

    }

    void Start()
    {
        string[] portArray = ScanPorts_TryFail();//使用试错函数，可以解决COM被占用问题
        OpenSerialPort(portArray[1], 115200, Parity.None, 8, StopBits.None);
        SendData("12345");
    }

    void Update()
    {
        //cubeTransform.localRotation = Quaternion.Euler((float)-y, (float)x, (float)z);
    }
    #endregion
}

