

/**
 * enum for activation function
 */

enum activationFunctionType{
	 None=0,
	 RELU=1,
	 SIGMOID=2,
     SOFTMAX=3,
     TANHYP=4
}



//% weight=70 icon="\u237E" color=#74DF00 block="AI"
namespace nntest {

    //% weight=100 
    //% blockId=nntest_initfcnn
    //% block="Init Brain|number %inputs|number[] %hidden|number %outputs"
    //% shim=nntest::initfcnn
    export function initfcnn(inputs: number, hidden: number[], outputs: number): void {
    	basic.showString("sim:init")
    }

    //% weight=90 
    //% blockId=nntest_fcnnfromjson
    //% block="Json Brain|string %json"
    //% shim=nntest::fcnnfromjson
    export function fcnnfromjson(json: string): void {
    	basic.showString("sim:json")
    }

    //% weight=80 
    //% blockId=nntest_setactivation
    //% block="Set Activation| %activationFunctionType"
    //% shim=nntest::setactivation
    export function setactivation(activation: activationFunctionType): void {
      switch(activation){
        case activationFunctionType.None: basic.showString("act=None")
        case activationFunctionType.RELU: basic.showString("act=RELU")
        case activationFunctionType.SIGMOID: basic.showString("act=SIGMOID")
        case activationFunctionType.SOFTMAX: basic.showString("act=SOFTMAX")
        case activationFunctionType.TANHYP: basic.showString("act=TANHYP")
        default: basic.showString("act=<invalid value>")
      }
    }


    //% weight=70 
    //% blockId=nntest_train
    //% block="Train|number[] %input|number[] %expected_output"
    //% shim=nntest::train
    export function train(input: number[], expected_output: number[]): void {
    	basic.showString("sim-train")
    }

    //% weight=60 
    //% blockId=nntest_ftrain
    //% block="Train with err result|number[] %input|number[] %expected_output"
    //% shim=nntest::ftrain
    export function ftrain(input: number[], expected_output: number[]): number {
    	basic.showString("sim-ftrain")
        return 1
    }

    //% weight=50 
    //% blockId=nntest_predict
    //% block="Predict|number[] %input|number[] %output"
    //% shim=nntest::predict
    export function predict(input: number[], output: number[]): void {
    	basic.showString("sim-predict")
    }


 }
