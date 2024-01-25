using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Test : MonoBehaviour
{
    public GameObject obj;
    public GameObject parsys;
    private GameObject obj_temp;
    private static float timer;
    private float scale_r; 
    private List<Snowflake> flakes;
    private List<Snowflake> helpflakes;

    // Start is called before the first frame update
    void Start()
    {
       timer = 0.0f;
       flakes = new List<Snowflake>(100);
       helpflakes = new List<Snowflake>();
       for(int i = 0; i < 100; i++)
        {
            obj_temp = Instantiate(obj, new Vector3(parsys.transform.position.x + Random.Range(-2.0f, 2.0f), parsys.transform.position.y, parsys.transform.position.z + Random.Range(-2.0f, 2.0f)), Quaternion.identity) as GameObject;
            scale_r = Random.Range(-0.1f, 0.1f);
            Vector3 v_scale_r = new Vector3(scale_r, scale_r, scale_r);
            obj_temp.transform.localScale += v_scale_r;
            flakes.Add(new Snowflake(obj_temp));
        }
    }

    // Update is called once per frame
    void Update()
    {
        timer += Time.deltaTime;

        for(int i=0; i<flakes.Count; i++)
        {
            if(timer - flakes[i].birth > flakes[i].ttl)
            {
                helpflakes.Add(flakes[i]);
                flakes[i].o.SetActive(false);
                Destroy(flakes[i].o);
            }
            flakes[i].o.transform.Translate(new Vector3(0, -1, 0) * flakes[i].speed * Time.deltaTime);
            scale_r = Random.Range(-0.05f, 0.05f);
            Vector3 v_scale_r = new Vector3(scale_r, scale_r, scale_r);
            flakes[i].o.transform.localScale += v_scale_r;
            flakes[i].o.GetComponent<Renderer>().material.color = Color.green;
        }

        for(int i=0;i<helpflakes.Count; i++)
        {
            flakes.Remove(helpflakes[i]);
            obj_temp = Instantiate(obj, new Vector3(parsys.transform.position.x + Random.Range(-2.0f, 2.0f), parsys.transform.position.y, parsys.transform.position.z + Random.Range(-2.0f, 2.0f)), Quaternion.identity) as GameObject;
            scale_r = Random.Range(-0.1f, 0.1f);
            Vector3 v_scale_r = new Vector3(scale_r, scale_r, scale_r);
            obj_temp.transform.localScale += v_scale_r;
            flakes.Add(new Snowflake(obj_temp));
        }
        helpflakes.Clear();
    }

    [System.Serializable]
    public class Snowflake
    {
        public GameObject o;
        public float ttl;
        public float birth;
        public float speed;

        public Snowflake(GameObject o)
        {
            this.o = o;
            this.ttl = Random.Range(0.5f, 1.5f);
            this.birth = Test.timer;
            this.speed = Random.Range(4.0f, 5.5f);
        }
    }
}

