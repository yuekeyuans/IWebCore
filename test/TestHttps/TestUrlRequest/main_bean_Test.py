import unittest

from beanTest.GetBeanTest import GetBeanTest
from beanTest.postBeanTest import PostBeanTest
from beanTest.GetTableTest import GetTableTest

cases = [GetBeanTest, PostBeanTest, GetTableTest]
# cases = [GetTableTest]
if __name__ == "__main__":
    suites = unittest.TestSuite()
    for case in cases:
            suite = unittest.TestLoader().loadTestsFromTestCase(case)
            suites.addTests(suite)
    unittest.TextTestRunner(verbosity=2).run(suites)
