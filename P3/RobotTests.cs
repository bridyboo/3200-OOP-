using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Tests
{
    [TestClass()]
    public class RobotTests
    {
        [TestMethod()]
        public void Test_move_willMoveRow()
        {
            //Arrange
            Robot rbt = new Robot("grid.txt");

            //Act
            rbt.move();

            int defaultRow = 5;
            bool ans = true;
            if (defaultRow == rbt.getRow())
                ans = !ans;

            //Assert
            Assert.IsTrue(ans);
        }

        [TestMethod()]
        public void test_moveOnce_willMoveRow()
        {
            //Arrange
            Robot rbt = new Robot("grid.txt");

            //Act
            rbt.moveOne();

            int defaultRow = 5;
            bool ans = true;
            if (defaultRow == rbt.getRow())
                ans = !ans;

            //Assert
            Assert.IsTrue(ans);
        }
    }
}