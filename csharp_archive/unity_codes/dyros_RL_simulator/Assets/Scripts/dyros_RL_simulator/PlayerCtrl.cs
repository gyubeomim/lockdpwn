using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class State_dyrosRL {
    public float[] sensor_data = new float[181];    // input array : 센서 0~180번

    public float engine = 0;     // output0 : 차량의 속도
    public float turn = 0;       // output1 : 차량의 회전

    public float reward = 1;     // 보상

    public int isDone = 0;       // 게임이 끝났는가?
    public int episode = 0;      // 에피소드

    public void reset() {
        for (int i = 0; i < sensor_data.Length; i++) {
            sensor_data[i] = 0;
        }

        reward = 1;
        episode = 0;
    }
}

public class PlayerCtrl : MonoBehaviour {
    public int max_Step = 3000;
    private int sensorLength = 181;
    private float[] sensorOutput;

    /// ed: 코드 추가
    public GameObject PrototypeCar;
    public GameMgr gameMgr;

    private SendPacket sendPacket;
    private State_dyrosRL state_dyrosRL;
    private Sensor[] sensors;
    private float timeSinceLastCheckpoint;


    /// <summary>
    /// Whether this car is controllable by user input (keyboard).
    /// </summary>
    public bool UseUserInput = false;

    /// <summary>
    /// The movement component of this car.
    /// </summary>
    public PlayerMovement Movement {
        get;
        private set;
    }

    /// <summary>
    /// The current inputs for controlling the CarMovement component.
    /// </summary>
    public double[] CurrentControlInputs {
        get { return Movement.CurrentInputs; }
    }

    /// <summary>
    /// The cached SpriteRenderer of this car.
    /// </summary>
    public SpriteRenderer SpriteRenderer {
        get;
        private set;
    }

    /// ed: 목표지점에 도착했는지 체크하는 변수
    private bool isInGoal = false;
    private bool isFail = false;


    /// ed: 플레이어가 죽은 경우 실행되는 코루틴함수
    IEnumerator StartResetEpisode() {
        yield return new WaitForFixedUpdate();
        //Transform tr = new Transform(0, 0, 0);

        this.transform.position = PrototypeCar.transform.position;
        //Vector3 gg = new Vector3(15, 0, 0);
        //this.transform.position = gg;

        this.transform.rotation = PrototypeCar.transform.rotation;
        Movement.enabled = true;
        timeSinceLastCheckpoint = 0;

        foreach (Sensor s in sensors)
            s.Show();

        this.enabled = true;
        this.isInGoal = true;
        this.isFail = false;

        ResetEpisode();
    }


    /// ed: 데이터를 받으면 실행되는 코루틴함수
    public IEnumerator Action_dyrosRL(float recv_data) {
        /// ed: socket으로부터 받은 output 데이터는 One Hot Vector이므로
        ///      아래와 같이 분기별로 다른 action sets 들을 만들어줘야합니다
        ///      각 분기별 값은 임의로 지정할 수 있습니다.\

        float act1 = 0.3f;
        float act2 = 0.8f;
 
        if (recv_data == 0) {
            Movement.SetInputs(0f, act1);
            Debug.Log("0 : [" + 0 + ", " + act1 + "]");
        }
        else if (recv_data == 1) {
            Movement.SetInputs(act1, 0f);
            Debug.Log("1 : [" + act1 + ", " + 0 + "]");
        }
        else if (recv_data == 2) {
            Movement.SetInputs(-act1, 0f);
            Debug.Log("2 : [" + -act1 + ", " + 0 + "]");
        }
        else if (recv_data == 3) {
            Movement.SetInputs(act1, act1);
            Debug.Log("3 : [" + act1 + ", " + act1 + "]");
        }
        else if (recv_data == 4) {
            Movement.SetInputs(-act1, act1);
            Debug.Log("4 : [" + -act1 + ", " + act1 + "]");
        }
        else if (recv_data == 5) {
            Movement.SetInputs(0f, act2);
            Debug.Log("5 : [" + 0 + ", " + act2 + "]");
        }
        else if (recv_data == 6) {
            Movement.SetInputs(act2, 0f);
            Debug.Log("6 : [" + act2 + ", " + 0 + "]");
        }
        else if (recv_data == 7) {
            Movement.SetInputs(-act2, 0f);
            Debug.Log("7 : [" + -act2 + ", " + 0 + "]");
        }
        else if (recv_data == 8) {
            Movement.SetInputs(act2, act2);
            Debug.Log("8 : [" + act2 + ", " + act2 + "]");
        }
        else if (recv_data == 9) {
            Movement.SetInputs(-act2, act2);
            Debug.Log("9 : [" + -act2 + ", " + act2 + "]");
        }

        //float[] tmp = new float[2];
        //tmp[0] = 0.0f;
        //tmp[1] = 0.1f;
        //Movement.SetInputs(tmp);

        /// ed: 에피소드를 하나 증가시키고
        state_dyrosRL.episode++;
        yield return new WaitForFixedUpdate();

        /// ed: Input으로 사용할 센서값을 받아오고
        UpdateState();
        /// ed: 차량과 부딪혔는지 검사합니다 
        CheckFail();
    }

    bool IsMaxStep() {
        if (state_dyrosRL.episode > max_Step)
            return true;
        return false;
    }

    
    /// ed: 차량이 부딪혔는지 체크하고 실행되는 함수
    public void CheckFail() {
        /// ed: 차량이 부딪혔다면
        if (isFail) {
            state_dyrosRL.isDone = 1;
            SocketServer.instance.SendMessage(ConvertData());
            //한 에피소드씩 재생할 때 사용
            StartCoroutine(StartResetEpisode());
            //ResetEpisode();

            
        }
        /// ed: 차량이 안 부딪힌 경우 실행되는 코드
        else
            SocketServer.instance.SendMessage(ConvertData());
    }


    /// ed: socket으로 전송할 센서값을 저장하는 함수
    void UpdateState() {
        /// ed: socket으로 전송하기 위해 센서들의 값을 저장합니다
        for (int i =0; i < sensors.Length; i++) {
            state_dyrosRL.sensor_data[i] = sensorOutput[i];
        }
    }


    private void Awake() {
        Movement = GetComponent<PlayerMovement>();
        sensors = GetComponentsInChildren<Sensor>();
        SpriteRenderer = GetComponent<SpriteRenderer>();

        sendPacket = new SendPacket();
        sendPacket.data = new float[sensorLength];
        state_dyrosRL = new State_dyrosRL();

        sensorOutput = new float[sensors.Length];
    }

    private void Start() {
        /// event 개념을 활용해서 HitCar 이벤트에 Die 함수를 연결한다
        Movement.HitCar += Die;
    }

    private void Update() {
        timeSinceLastCheckpoint += Time.deltaTime;
    }


    void FixedUpdate() {
        /// ed: 센서값을 받아오는 코드
        for (int i = 0; i < sensors.Length; i++) {
            sensorOutput[i] = sensors[i].Output;
        }

        /// ed: 목표지점을 설정하고
        Bounds bounds = new Bounds(new Vector3(38, -65, 0),new Vector3(3,3,0));

        /// ed: 현재차량이 목표지점(Goal)에 도착하면 아래 코드가 시작된다
        if (bounds.Contains(this.transform.position)) {
            if (!isInGoal) {
                Debug.Log("Goal!");

                state_dyrosRL.reward = 100;
                isInGoal = true;
            }
        }
    }

    /// ed: agent가 벽에 부딪히는 경우 실행되는 함수 (이벤트에 의해 실행된다)
    // Makes this car die (making it unmovable and stops the Agent from calculating the controls for the car).
    private void Die() {
        this.enabled = false;
        Movement.Stop();
        Movement.enabled = false;

        foreach (Sensor s in sensors)
            s.Hide();

        
        this.isFail = true;
    }

    /// ed: 에피소드를 재시작하는 함수
    void ResetEpisode() {
        state_dyrosRL.reset();
        state_dyrosRL.isDone = 0;

        SocketServer.instance.SendMessage(ConvertData());
    }


    /// ed: 시뮬레이션 데이터를 socket 전송데이터로 변환하는 함수
    public SendPacket ConvertData() {
        for (int i = 0; i < sensorLength; i++)  {
            //Debug.Log(sendPacket.data.Length);
            //Debug.Log(state_dyrosRL.sensor_data.Length);
            sendPacket.data[i] = state_dyrosRL.sensor_data[i];
        }
        sendPacket.isDone = state_dyrosRL.isDone;
        sendPacket.reward = state_dyrosRL.reward;

        //Debug.Log("s0: " + sendPacket.data[0]);
        //Debug.Log("good90: " + sendPacket.data[90]);
        //Debug.Log("s180: " + sendPacket.data[180]);

        return sendPacket;
    }

}
