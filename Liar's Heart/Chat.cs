using System.Collections;
using System.Diagnostics;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using TMPro;

public class Chat : MonoBehaviour
{
    // Python Server
    private readonly string pythonPath = Application.streamingAssetsPath + @"\Scripts\dist\main\main.exe";
    private Process pythonProcess;

    private const string serverIP = "127.0.0.1";
    private const int serverPort = 25001;
    private NetworkStream stream;
    private TcpClient client;

    // Chat UI
    [SerializeField] private TMP_Text titleText;
    [SerializeField] private TMP_Text subtitleText;
    [SerializeField] private TMP_InputField inputField;

    // Chat Message
    [SerializeField] private Transform parent;
    [SerializeField] private GameObject ChatMessagePrefab;

    void Awake()
    {
        RunPythonServer();
    }

    void Start()
    {
        Connect(); // Server

        inputField.onValueChanged.AddListener(delegate { OnValueChangedEvent(); });
        inputField.onEndEdit.AddListener(delegate { OnEndEditEvent(); });
    }

    private void AddChat()
    {
        // Create Chat Message UI
        UIChatMessage clone = Instantiate(ChatMessagePrefab, parent).GetComponent<UIChatMessage>();
        clone.Init(GameManager.Character.GetMainCharacter);
        clone.SetText(inputField.text.ToString());

        // Send To Server
        string streamWriteData = GameManager.Character.InvestigateCharacter.name + "!@#$$#@!" + inputField.text.ToString();
        Send(streamWriteData);

        // Init Input Filed
        inputField.text = " ";
        inputField.readOnly = true;

        StartCoroutine(AddAIChat());
    }

    private IEnumerator AddAIChat()
    {
        yield return Receive();
    }

    private async Task Receive()
    {
        byte[] buffer = new byte[client.ReceiveBufferSize];
        int length = await stream.ReadAsync(buffer, 0, client.ReceiveBufferSize);
        string retval = Encoding.UTF8.GetString(buffer, 0, length);

        string[] answer_emotion = retval.Split("!@#$$#@!");
        string answer = answer_emotion[0];
        string emotion = answer_emotion[1];

        // Create Chat Message UI
        UIChatMessage clone = Instantiate(ChatMessagePrefab, parent).GetComponent<UIChatMessage>();
        clone.Init(GameManager.Character.InvestigateCharacter);
        clone.SetText(answer);

        // Set Emotion
        GameManager.HeartRate.SetEmotionByHeartRate(emotion);
    }

    // InputField Event
    public void OnEndEditEvent()
    {
        if (Input.GetKeyDown(KeyCode.Return))
        {
            if (inputField.text.Equals(""))
            {
                return;
            }
        }
    }

    // InputField Event
    public void OnValueChangedEvent()
    {
        if (inputField.text.Equals("\n"))
        {
            inputField.text = inputField.text.Replace("\n", "");
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    // Server
    private void Connect()
    {
        try
        {
            client = new TcpClient(serverIP, serverPort);
            stream = client.GetStream();
        }
        catch (SocketException e)
        {
            UnityEngine.Debug.Log("Socket connection failed: " + e.Message);
        }
    }

    private void Send(string packet)
    {
        byte[] buffer = Encoding.UTF8.GetBytes(packet);
        stream.Write(buffer, 0, buffer.Length);

        UnityEngine.Debug.Log("Send: " + packet);
    }

    private void RunPythonServer()
    {
        // Set start info
        ProcessStartInfo startinfo = new ProcessStartInfo();
        startinfo.FileName = pythonPath;
        startinfo.UseShellExecute = false;
        startinfo.RedirectStandardOutput = true;
        startinfo.CreateNoWindow = true;

        // Create Process
        pythonProcess = new Process();
        pythonProcess.StartInfo = startinfo;
        pythonProcess.Start();
    }

    private void ExitPythonServer()
    {
        pythonProcess.Kill();
        pythonProcess.Dispose();
    }

    private void OnApplicationQuit()
    {
        ExitPythonServer();
    }
}
