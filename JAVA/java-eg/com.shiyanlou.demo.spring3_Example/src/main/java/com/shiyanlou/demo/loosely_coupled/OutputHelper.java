package com.shiyanlou.demo.loosely_coupled;

public class OutputHelper {
    private IOutputGenerator outputGenerator = null;

    public void generateOutput() {
        this.outputGenerator.generateOutput();
    }

    public void setOutputGenerator(IOutputGenerator outputGenerator) {
        this.outputGenerator = outputGenerator;
    }
}
