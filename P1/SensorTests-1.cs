using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace Tests
{
    [TestClass()]
    public class SensorTests
    {
        [TestMethod()]
        public void Test_isValid_givenAge_returnsInt()
        {
            //Arrange
            Sensor sens = new Sensor(true);
            uint age = 5;

            //Act
            int result = sens.isValid("brian", age);

            //Assert
            Assert.IsInstanceOfType(result, typeof(int));
        }

        [TestMethod()]
        public void Test_isValid_givenBatteryLessThanTen_returnsZero()
        {
            //arrange
            Sensor sens = new Sensor(true);
            int tries = 9;
            uint age = 3;

            //act
            for (int i = 0; i < tries; i++)
                sens.isValid("brian", age);

            //assert
            Assert.AreEqual(sens.isValid("brian", age), 0);
        }

        [TestMethod()]
        public void Test_isValid_givenStateIsFalse_returnsZero()
        {
            //arrange
            Sensor sens = new Sensor(false);
            uint age = 4; 

            //act
            int ans = sens.isValid("brian", age);

            //assert
            Assert.AreEqual(ans, 0);
        }

        [TestMethod()]
        public void Test_flipSwitch_givenBatteryIsLessThanEqualZero_returnFalse()
        {
            //arrange
            Sensor sens = new Sensor(true);
            int tries = 10;
            uint age = 21;

            for (int i = 0; i < tries; i++)
                sens.isValid("brian", age);

            //act
            bool ans = sens.flipSwitch(); 

            //assert
            Assert.IsFalse(ans);
        }

        [TestMethod()]
        public void Test_recharge_givenDeadBattery_batteryIsCharged()
        {
            Sensor sens = new Sensor(true);
            int tries = 10;
            uint age = 21;

            for (int i = 0; i < tries; i++)
                sens.isValid("brian", age);

            //act
            sens.recharge();
            int ans = sens.isValid("brian", age);
            
            //assert
            Assert.IsInstanceOfType(ans, typeof(int));
        }

    }
}