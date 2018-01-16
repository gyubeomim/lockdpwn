using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameMgr : MonoBehaviour {
    /// 차량이 생성되는 Point를 담은 배열
    public Transform[] points;

    /// 차량의 프리팹
    public GameObject carPrefab;

    /// 차량을 미리 생성해서 저장할 리스트 자료형 (Object Pooling 기법)
    public List<GameObject> carPool = new List<GameObject>();

    public float createTime = 2.0f;
    public bool isGameOver = false;

    /// 최대 차량개수
    public int maxCarNum = 5;

    /// 싱글턴 패턴을 위한 인스턴스 변수 선언
    public static GameMgr instance = null;


    private void Awake() {
        /// 게임클래스를 인스턴스에 삽입
        instance = this;
    }


    /// 차량을 생성하는 코루틴함수
    IEnumerator CreateCar() {
        while (!isGameOver) {
            /// 차량의 생성주기만큼 메인루프에 양보
            yield return new WaitForSeconds(createTime);

            /// 게임이 끝난 경우 코루틴을 종료한다
            if (isGameOver) yield break;

            /// 오브젝트풀의 리스트 루프를 돌면서
            foreach (GameObject car in carPool) {
                /// 비활성화 여부로 사용가능한 차량을 판단한다
                if (!car.activeSelf) {

                    /// 차량을 출현시킬 인덱스값을 뽑고
                    int idx = Random.Range(1, points.Length);

                    /// 차량의 출현위치를 정하고 활성화시킨다
                    car.transform.position = points[idx].position;
                    car.SetActive(true);

                    /// 차량프리팹 하나를 활성화한 다음 for Loop을 빠져나간다
                    break;
                }
            }
        }
    }

	void Start () {
        points = GameObject.Find("SpawnPoint").GetComponentsInChildren<Transform>();

        for(int i = 0; i < maxCarNum; i++) {
            GameObject car = Instantiate(carPrefab);
            
            car.name = "Obstacle_Vehicle(Clone)" + i.ToString();
            car.SetActive(false);
            carPool.Add(car);
        }

        if (points.Length > 0)
            StartCoroutine(this.CreateCar());

	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
