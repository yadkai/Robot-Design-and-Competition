# Robot Design and Competition - 2021 Team: Yadkai

 ## The tasks of the competition.
 <div class="row">
  <div class="column">
 <img style="width:100%" alt="snow" src="https://user-images.githubusercontent.com/66894143/201977980-a7c7d974-a02a-4864-b63a-cf6124ef0e04.PNG">
   </div>
  
</div>

 
 <ul><li>
 Line following
 <ul> <li>
 the robot must follow a white line on a black surface. These paths may contain straight

 lines, curved lines, or dotted line segments.
 </li></ul>  </li>
 <li>
 Wall maze
 <ul> <li>
  After a line following section, the robot will have to navigate through a wall maze
 section. This maze will not contain any looping paths. (A single possible path from
 start to end is guaranteed.)
  </li></ul>  </li>
 <li>
 Mosaic Floor Area
  <ul> <li>
 The robot exiting the wall maze should immediately enter the mosaic floor area and
 proceed to complete the following subtasks. Inserting the key solids to respective
 keyholes to close the bridge. Collecting the ball of the color assigned to your team at
 the start of the competition.
 </li></ul>  </li>
 <li>
 Bridge
  <ul> <li>
 The robot should cross the closed bridge and exit the area to a dotted line segment.
   </li></ul>  </li>
 <li>
 Shooting area
  <ul> <li>
 The robot must choose the correct path at the Y junction area according to the color
 assigned. While staying in the restricted space, the robot will have to shoot the
 collected ball through the goal.
   </li></ul>  </li></ul>


## The Task Follow & Approch

![Algorithm - Frame 6](https://user-images.githubusercontent.com/66894143/201981973-b707f79f-28df-4089-b2ec-02ca5b5b0f63.jpg)


## Algorithm




<div class="row">
  <div class="column">
   <h3>PID Line Following</h3><br>
    <img style="width:40%" alt="Capture3" src="https://user-images.githubusercontent.com/66894143/201984123-200d2133-9f00-41ce-b9dd-91d69e15658d.PNG">
  </div>
  <div class="column">
   <h3>PID Maze Solving</h3><br>
   <img width="836" alt="Capture4" src="https://user-images.githubusercontent.com/66894143/201985226-1ea4c48f-bd3a-49f3-8273-dc55b32b7bd7.PNG">
  </div>
  <div class="column">
    <h3>Mosic Floor Navigation</h3><br>
    <img width="394" alt="Capture5" src="https://user-images.githubusercontent.com/66894143/201986368-1246d559-3090-45a0-8d36-77fc20c8d29e.PNG">
  </div>
 
 <div class="column">
    <h3>Arm Manipulation Inverse Kinematics  </h3><br>
    <img width="719" alt="Capture6" src="https://user-images.githubusercontent.com/66894143/201987007-5f7a15ec-2da9-4d0f-9d81-175312de111f.PNG">
  </div>
 
 
 

 
</div>

<h3>Simulation Results</h3><br>
https://user-images.githubusercontent.com/66894143/201988013-1d7b4f7e-3c3f-4fa1-818d-8d1f78bc4626.mp4






https://user-images.githubusercontent.com/66894143/201989404-deedcabc-5eeb-4a56-85ab-d73e415cb2a8.mp4



https://user-images.githubusercontent.com/66894143/201989577-d604b9ec-ffc9-4a25-a804-832a2130c638.mp4



https://user-images.githubusercontent.com/66894143/201989594-74f4caee-fe07-4f68-b390-5d05d256f230.mp4



https://user-images.githubusercontent.com/66894143/201989644-856a7c58-4d2e-4540-b92b-0553b5ee5305.mp4

