# Demo 1: Basic Sequential Behavior
In this demo, we'll create a simple Behavior Tree that represents a basic sequential behavior. The entity will perform three actions in sequence: "Initialize," "Execute Task 1," and "Execute Task 2."

## BT Design
The behavior tree for this demo will consist of three Action nodes arranged in a sequence:
```
[Root]
  |
  └── [Sequence]
        |
        ├── [Action: Initialize]
        |
        ├── [Action: Execute Task 1]
        |
        └── [Action: Execute Task 2]
```