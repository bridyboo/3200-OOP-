using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Tests
{
    [TestClass()]
    public class SensorTests
    {
        [TestMethod()]
        public void isValidTest_when1_true()
        {
            //arrange
            Sensor sens = new Sensor(true);

            //act
            bool ans = sens.isValid(1);

            //assert
            Assert.IsTrue(ans);
        }

        [TestMethod()]
        public void isValidTest_when0_true()
        {
            //arrange
            Sensor sens = new Sensor(true);

            //act
            bool ans = sens.isValid(0);

            //assert
            Assert.IsFalse(ans);
        }

    }
}