using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Tests
{
    [TestClass()]
    public class ActuatorTests
    {
        [TestMethod()]
        public void moveForwardTest()
        {
            //Arrange
            Actuator act = new Actuator("down");

            //Act
            int row = 5;
            int col = 5;
            int ans = act.moveForward(row, col);

            //Assert
            Assert.AreNotEqual(row, ans);
        }

    }
}