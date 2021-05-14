var valore;
var dati;
socket.on('stuffwithserial', function (data) {
    dati = data;
    valore = dati.substring(1);
    if (dati.charAt(0) == 'H') {
        document.getElementById("Battito").value = valore;
    }
    else if (dati.charAt(0) == 'S'){
        document.getElementById("Ossigenazione").value = valore;
    }
});