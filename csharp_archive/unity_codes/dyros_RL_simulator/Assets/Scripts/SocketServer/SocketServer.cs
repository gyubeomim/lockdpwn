using UnityEngine;
using System;
using System.IO;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using System.Runtime.InteropServices;
using System.Collections;

[Serializable]
public struct SendPacket {
    /// ed: float[]를 가진 구조체를 byte[]로 변환하기 위해서는 아래코드를 추가해야 한다
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 500)]
    public float[] data;    // sensors data

    public float isDone;      // isDone
    public float reward;      // reward
}

[Serializable]
public struct RecvPacket {
    /// ed: DQN으로부터 나오는 action값이 one_hot_vector와 같이 하나의 값만 가질 수 있으므로
    /// 아래와 같이 1개의 데이터만 받는다
    public float recv_data;      
}

class SocketServer : MonoBehaviour {
    public static SocketServer instance;
    public PlayerCtrl playerCtrl;
    Socket SeverSocket = null;
    Thread Socket_Thread = null;
    bool Socket_Thread_Flag = false;

    SendPacket sendData;
    RecvPacket recvData;
    bool isRecved;

    IPEndPoint ipep;
    Socket client;
    IPEndPoint clientep;
    NetworkStream recvStm;
    NetworkStream sendStm;

    void Awake() {
        instance = this;
        Socket_Thread = new Thread(Dowrk);
        Socket_Thread_Flag = true;
        Socket_Thread.Start();

        isRecved = false;
        recvData = new RecvPacket();
        sendData = new SendPacket();

        /// ed: input으로 사용할 data, isDone 변수값을 초기화합니다
        sendData.data = new float[181];
        for (int i = 0; i < sendData.data.Length; i++) {
            sendData.data[i] = 0;
        }

        sendData.isDone = 0;
        sendData.reward = 1;
    }

    /// ed: 일정한 간격으로 실행되는 함수
    private void FixedUpdate() {
        //Debug.Log(isRecved);
        /// ed: 데이터를 받으면
        if (isRecved) {
            /// ed: 받은 데이터를 사용해서 아래와 같은 코루틴함수를 실행합니다
            //Debug.Log("[+] recv data : " + recvData.recv_data);
            StartCoroutine(playerCtrl.Action_dyrosRL(recvData.recv_data));
            isRecved = false;
        }
    }


    // byte 배열을 구조체로
    public static T ByteToStruct<T>(byte[] buffer) where T : struct {
        int size = Marshal.SizeOf(typeof(T));

        if (size > buffer.Length) {
            throw new Exception();
        }

        IntPtr ptr = Marshal.AllocHGlobal(size);
        Marshal.Copy(buffer, 0, ptr, size);
        T obj = (T)Marshal.PtrToStructure(ptr, typeof(T));
        Marshal.FreeHGlobal(ptr);
        return obj;
    }


    // 구조체를 byte 배열로
    public static byte[] StructureToByte(object obj) {
        int datasize = Marshal.SizeOf(obj);             //((PACKET_DATA)obj).TotalBytes; // 구조체에 할당된 메모리의 크기를 구한다.
        IntPtr buff = Marshal.AllocHGlobal(datasize);   // 비관리 메모리 영역에 구조체 크기만큼의 메모리를 할당한다.
        Marshal.StructureToPtr(obj, buff, false);       // 할당된 구조체 객체의 주소를 구한다.
        byte[] data = new byte[datasize];               // 구조체가 복사될 배열
        Marshal.Copy(buff, data, 0, datasize);          // 구조체 객체를 배열에 복사
        Marshal.FreeHGlobal(buff);                      // 비관리 메모리 영역에 할당했던 메모리를 해제함

        return data;                                    // 배열을 리턴
    }


    private void Dowrk() {
        SeverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        ipep = new IPEndPoint(IPAddress.Any, 8080);
        SeverSocket.Bind(ipep);
        SeverSocket.Listen(10);

        Debug.Log("소켓 대기중....");
        client = SeverSocket.Accept();     //client에서 수신을 요청하면 접속합니다.
        Debug.Log("소켓 연결되었습니다.");

        clientep = (IPEndPoint)client.RemoteEndPoint;
        recvStm = new NetworkStream(client);
        sendStm = new NetworkStream(client);

        while (Socket_Thread_Flag) {
            byte[] receiveBuffer = new byte[256];
            try {
                //Debug.Log("[+] receiveBuffer Length : " + receiveBuffer.Length);
                recvStm.Read(receiveBuffer, 0, receiveBuffer.Length);

                //Debug.Log("[+] receiveBuffer2 : " + Encoding.ASCII.GetString(receiveBuffer));
                recvData = ByteToStruct<RecvPacket>(receiveBuffer);

                //Debug.Log("[+] recvData engine : " + recvData.engine);

                isRecved = true;
            }
            catch (Exception e) {
                Debug.Log(e.Message);
                Socket_Thread_Flag = false;
                client.Close();
                SeverSocket.Close();
                continue;
            }
        }
    }

    public void SendMessage(SendPacket sendData) {
        //Debug.Log("sendData : " + sendData.data.Length);
        byte[] packetArray = StructureToByte(sendData);

        //Debug.Log("packetArray : " + Encoding.ASCII.GetString(packetArray));
        //Debug.Log("packetArray Length : " + packetArray.Length);
        sendStm.Write(packetArray, 0, packetArray.Length);
    }

    void OnApplicationQuit() {
        try {
            Socket_Thread_Flag = false;
            Socket_Thread.Abort();
            SeverSocket.Close();
        }
        catch {
            Debug.Log("소켓과 쓰레드 종료때 오류가 발생");
        }
    }


}