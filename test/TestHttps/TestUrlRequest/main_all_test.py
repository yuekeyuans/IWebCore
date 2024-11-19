import unittest
from unittest.suite import TestSuite

from resultTest.ByteArrayReturnTest import ByteArrayReturnTest
from resultTest.RedirectUrlReturnTest import RedirectUrlReturnTest
from resultTest.JsonReturTest import JsonReturTest
from resultTest.HtmlReturnTest import HtmlReturnTest
from resultTest.DefaultPathReturnTest import DefaultPathReturnTest
from resultTest.PostTextParameterTest import PostTextParameterTest
from resultTest.TextReturnTest import TextReturnTest
from resultTest.PostMultiPartTest import PostMultiPartTest
from resultTest.HttpMethodTest import HttpMethodTest
from resultTest.PostMethodTest import PostMethodTest
from resultTest.BeanReturnControllerTest import BeanReturnControllerTest
from resultTest.BeanParameterControllerTest import BeanParameterControllerTest;
from resultTest.ReqRespOperatorOverrideControllerTest import ReqRespOperatorOverrideControllerTest
from resultTest.StaticFileReturnTest import StaticFileReturnTest


testCases = [
    ByteArrayReturnTest, RedirectUrlReturnTest, 
    JsonReturTest, PostMethodTest, HtmlReturnTest,
    DefaultPathReturnTest, PostTextParameterTest,
    TextReturnTest, PostMultiPartTest, 
    HttpMethodTest, BeanReturnControllerTest,
    BeanParameterControllerTest, ReqRespOperatorOverrideControllerTest, HtmlReturnTest,
    StaticFileReturnTest
    ]

if __name__ == '__main__':
    suites = TestSuite()

    for case in testCases:
        suite = unittest.TestLoader().loadTestsFromTestCase(case)
        suites.addTests(suite)
    unittest.TextTestRunner(verbosity=2).run(suites)
    