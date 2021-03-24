using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Tests
{
    [TestClass()]
    public class RotatingRobotTests
    {
        [TestMethod()]
        public void moveOnceRight_rotateRight()
        {
            //Arrange
            RotatingRobot rbt = new RotatingRobot("grid.txt");

            //Act
            rbt.rotate();
            rbt.moveOne();

            bool ans = true;
            int defaultCol = 5;
            if (defaultCol == rbt.getCol())
                ans = !ans;

            //Assert
            Assert.IsTrue(ans);
        }

        [TestMethod()]
        public void moveOnceLeft_rotateLeft()
        {
            //Arrange
            RotatingRobot rbt = new RotatingRobot("grid.txt");

            //Act
            for (int i = 0; i < 3; i ++)
                rbt.rotate();
            rbt.moveOne();

            bool ans = true;
            int defaultCol = 5;
            if (defaultCol == rbt.getCol())
                ans = !ans;

            //Assert
            Assert.IsTrue(ans);
        }

        [TestMethod()]
        public void moveOnceUp_rotateUp()
        {
            //Arrange
            RotatingRobot rbt = new RotatingRobot("grid.txt");

            //Act
            for (int i = 0; i < 4; i++)
                rbt.rotate();
            rbt.moveOne();

            bool ans = true;
            int defaultRow = 5;
            if (defaultRow == rbt.getRow())
                ans = !ans;

            //Assert
            Assert.IsTrue(ans);
        }


    }
}