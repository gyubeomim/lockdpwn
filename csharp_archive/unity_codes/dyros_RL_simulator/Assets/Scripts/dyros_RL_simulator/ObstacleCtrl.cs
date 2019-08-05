using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObstacleCtrl : MonoBehaviour {
    private Vector3 targetPosition;
    private GameObject carGameobject;
    private Transform carTr;

    public float car_vel;

    /// ed: 센서 추가
    private Sensor[] sensors;

    /// 차량의 사라짐 여부
    private bool isDie = false;

    private void Awake() {
        carTr = gameObject.GetComponent<Transform>();
        sensors = GetComponentsInChildren<Sensor>();
    }

    // Use this for initialization
    void Start() {
        targetPosition.x = carTr.position.x;
        targetPosition.y = -120;

        car_vel = Random.Range(0.4f, 0.9f);
    }

    // Update is called once per frame
    void Update() {
        float dist = (Mathf.Min(sensors[0].Output, sensors[1].Output, sensors[2].Output));

        if (dist < 5f) {
            if (dist < 1f) {
                carTr.position = Vector3.MoveTowards(carTr.position, targetPosition, 0.05f);
            }
            else {
                carTr.position = Vector3.MoveTowards(carTr.position, targetPosition, 0.4f);
            }
        }
        else {
            carTr.position = Vector3.MoveTowards(carTr.position, targetPosition, car_vel);
        }



        /// ed: x 방향으로 차선이 바뀌지 않도록 아래 코드를 추가한다
        if (targetPosition.x != carTr.position.x)
            targetPosition.x = carTr.position.x;


        /// ed: 차량의 자세도 180를 유지하도록 합니다
        if (carTr.rotation.z != 180) {
            var angles = transform.rotation.eulerAngles;
            angles.z = 180;
            carTr.rotation = Quaternion.Euler(angles);
        }

        if (carTr.position.y <= -110) {
            isDie = true;
            gameObject.SetActive(false);
        }
        //if (isDie) Destroy(gameObject);
    }
}
