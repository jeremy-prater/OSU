﻿using System.Reflection;
using Android.App;
using Android.OS;
using Xamarin.Android.NUnitLite;
using Feature1;

namespace UnitTest1
{
    [Activity(Label = "UnitTest1", MainLauncher = true, Icon = "@drawable/icon")]
    public class MainActivity : TestSuiteActivity
    {
        protected override void OnCreate(Bundle bundle)
        {
            // tests can be inside the main assembly
            //AddTest(Assembly.GetExecutingAssembly());
            // or in any reference assemblies
            AddTest (typeof (Feature1.Class1).Assembly);

            // Once you called base.OnCreate(), you cannot add more assemblies.
            base.OnCreate(bundle);
        }
    }
}

