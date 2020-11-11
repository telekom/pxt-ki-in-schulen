serial.writeLine("START")
nntest.fcnnfromjson("{ \t\"params\": [ \t\t{\"input_layer_size\": 3},  \t\t{\"output_layer_size\": 3},  \t\t{ \t\t\t\"activation\": \"tanh\",  \t\t\t\"hidden_layer_sizes\": [3] \t\t} \t],      \"coefs\": [ \t\t[ \t\t\t[1.0, 0.0, 0.0],  \t\t\t[0.0, 1.0, 0.0],  \t\t\t[0.0, 0.0, 1.0] \t\t], \t\t[ \t\t\t[1.0, 2.0, 3.0],  \t\t\t[4.0, 5.0, 6.0],  \t\t\t[7.0, 8.0, 9.0] \t\t] \t], \t\"intercepts\": [ \t\t[ \t\t\t0.0, \t\t\t0.0, \t\t\t0.0 \t\t], \t\t[ \t\t\t0.0, \t\t\t0.0, \t\t\t0.0 \t\t] \t] }")
let ergebnis = [0, 0, 0]
nntest.predict([1, 2, 3], ergebnis)
serial.writeNumbers(ergebnis)
serial.writeLine("STOP")
