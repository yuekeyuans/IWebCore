import unittest

from resultTest.PostMethodTest import PostMethodTest
from resultTest.PostTextParameterTest import PostTextParameterTest
from resultTest.HttpMethodTest import HttpMethodTest
from resultTest.ByteArrayReturnTest import ByteArrayReturnTest
from resultTest.BeanReturnControllerTest import BeanReturnControllerTest
from resultTest.BeanParameterControllerTest import BeanParameterControllerTest
from resultTest.ReqRespOperatorOverrideControllerTest import ReqRespOperatorOverrideControllerTest
from resultTest.PostMultiPartTest import PostMultiPartTest
from resultTest.StaticFileReturnTest import StaticFileReturnTest

cases = [StaticFileReturnTest]
if __name__ == "__main__":
    suites = unittest.TestSuite()
    for case in cases:
            suite = unittest.TestLoader().loadTestsFromTestCase(case)
            suites.addTests(suite)
    unittest.TextTestRunner(verbosity=2).run(suites)
