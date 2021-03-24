using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Tests
{
    [TestClass()]
    public class TranRobotTests
    {

        [TestMethod()]
        public void DownTest_willMoveRow()
        {
            //arrange
            TranRobot tr = new TranRobot("grid.txt");

            //act
            tr.Down();

            bool ans = true;
            int defaultRow = 5;
            if (defaultRow == tr.getRow())
                ans = !ans;

            //assert
            Assert.IsTrue(ans);
        }

        [TestMethod()]
        public void LeftTest()
        {
            //arrange
            TranRobot tr = new TranRobot("grid.txt");

            //act
            tr.Left();

            bool ans = true;
            int defaultCol = 5;
            if (defaultCol == tr.getCol())
                ans = !ans;

            //assert
            Assert.IsTrue(ans);
        }

        [TestMethod()]
        public void RightTest()
        {
            //arrange
            TranRobot tr = new TranRobot("grid.txt");

            //act
            tr.Left();

            bool ans = true;
            int defaultCol = 5;
            if (defaultCol == tr.getCol())
                ans = !ans;

            //assert
            Assert.IsTrue(ans);
        }

        [TestMethod()]
        public void moveTest()
        {
            //arrange
            TranRobot tr = new TranRobot("grid.txt");

            //act
            tr.moveOne();

            bool ans = true;
            int defaultRow = 5;
            if (defaultRow == tr.getRow())
                ans = !ans;

            //assert
            Assert.IsTrue(ans);
        }
    }
}