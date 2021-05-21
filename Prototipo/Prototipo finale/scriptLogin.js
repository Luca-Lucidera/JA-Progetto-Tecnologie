let arrayData = []; //array di oggetti che conterrà le informazioni di un utente
var numel = 0; //numero di elementi presenti nel vettore
var obj_csv = {
    size: 0,
    dataFile: [],
};
var nome,cognome;
function export_csv() {
    //crea il csv vero e proprio
    let csv = "";
    arrayData.forEach((obj) => {
        let row = [];
        for (key in obj) {
            if (obj.hasOwnProperty(key)) {
                row.push(obj[key]);
            }
        }
        csv += row.join(",") + "\n";
        alert(csv);
    });
    let csvData = new Blob([csv], { type: "text/csv" });
    let csvUrl = URL.createObjectURL(csvData);
    let hiddenElement = document.createElement("a");
    hiddenElement.href = csvUrl;
    hiddenElement.target = "_blank";
    hiddenElement.download = "utenti_registrati" + ".csv";
    hiddenElement.click();
}

//legge il file;
function readImage(input) {
    //console.log(input)
    if (input.files && input.files[0]) {
        //console.log(input.files[0]);
        let reader = new FileReader();
        reader.readAsBinaryString(input.files[0]);
        reader.onload = function (e) {
            //console.log(e);
            obj_csv.size = e.total;
            obj_csv.dataFile = e.target.result;
            console.log(obj_csv.dataFile);
            parseData(obj_csv.dataFile);
        };
    }
}

function parseData(data) {
    let csvData = [];
    let lbreak = data.split("\n");
    lbreak.forEach((res) => {
        csvData.push(res.split(","));
    });
    arrayData = csvData;
    numel = arrayData.length - 1;
    console.log("arraydata ->", arrayData);
}

function manda() {
    (nome = document.getElementById("nome").value),
        (cognome = document.getElementById("cognome").value),
        (email = document.getElementById("email").value),
        (password = document.getElementById("pass").value);

    if (
        nome.search(/[-+]?[0-9]*\.?[0-9]+/g) == -1 &&
        cognome.search(/[0-9]/g) == -1
    ) {
        if (
            /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*$/.test(email)
        ) {
            if (password.length > 7) {
                arrayData[numel] = {
                    nome: document.getElementById("nome").value,
                    cognome: document.getElementById("cognome").value,
                    email: document.getElementById("email").value,
                    password: document.getElementById("pass").value,
                };
                numel++;
                alert("dati inseriti");
            } else {
                alert("la password deve contenere più di 8 caratteri");
            }
        } else {
            alert("Ricontrolla la mail");
        }
    } else {
        alert("il nome e il cognome non devono contenere dei numeri");
    }
}

function logga() {
    utenteRegistrato = false;
    for(var i = 0; i < arrayData.length - 1; i++){
        if(arrayData[i][2] == document.getElementById("email").value && arrayData[i][3] == document.getElementById("pass").value){
            alert("login effettuato");
            utenteRegistrato = true;
            nome = document.getElementById("nome").value;
            cognome = document.getElementById("cognome").value;
            localStorage.setItem("nome",nome);
            localStorage.setItem("cognome",cognome);
            window.location.href = "temperatura.html";
            //console.log(nomeLogEff," ",cognomeLogEff);
            //document.getElementById("ht").innerHTML='<object type="text/html" data="loginEffettuato.html" ></object>';
        }
    }
    if(utenteRegistrato == false){
        alert('Utente non registrato, premere pulsante "REGISTRATI"!');
    }
}

function loginEffettuato(){
    document.getElementById("nomeBenvenuto").innerHTML = localStorage.getItem("nome");
    document.getElementById("cognomeBenvenuto").innerHTML = localStorage.getItem("cognome");
}