#ifndef ANARI_LAYERINSTANCE_TESTS_HPP
#define ANARI_LAYERINSTANCE_TESTS_HPP

#include "pawlib/goldilocks.hpp"
#include "anari/transformation.hpp"
#include "anari/layerinstance.hpp"
#include "Eigen/Core"

class TestDefaultConstructor : public Test
{
    public:
        testdoc_t get_title()
        {
            return "LayerInstance Empty Constructor";
        }

        testdoc_t get_docs()
        {
            return "Create a new LayerInstance object and test the default constructor.";
        }

        bool run()
        {
            // Create a new LayerInstance object
            LayerInstance test_instance = LayerInstance();
            for (int i = 0; i < DIMENSION; i++)
            {
                for (int j = 0; j < DIMENSION; j++)
                {
                    // Check to see if initialization ws correctly performed
                    PL_ASSERT_EQUAL(test_instance.transform.the_matrix(i, j), 0);
                }
            }
            //PL_ASSERT_EQUAL(test_instance.transform, Transformation());
            return true;
        }
};

class TestConstructor : public Test
{
    public:
        testdoc_t get_title()
        {
            return "LayerInstance Constructor";
        }

        testdoc_t get_docs()
        {
            return "Create a new LayerInstance object and test the constructor.";
        }

        bool run()
        {
            Matrix3d test_matrix;
            test_matrix << 1,2,3,   // NOTE: This is a legal operation as defined by the Eigen Library.
                           4,5,6,   // Please refer to Eigen 3.2.10 in The Matrix class heading >>
                           7,8,9;   // Dense matrix and array manipulation >> comma initialization
            Transformation test_transform = Transformation(test_matrix);
            LayerInstance test_instance = LayerInstance(test_transform);

            for (int i = 0; i < DIMENSION; i++)
            {
                for (int j = 0; j < DIMENSION; j++)
                {
                    PL_ASSERT_EQUAL(test_instance.transform.the_matrix(i, j), test_matrix(i, j));
                }
            }
            return true;
        }
};

class TestCopyConstructor : public Test
{
     public:
        testdoc_t get_title()
        {
            return "LayerInstance Copy Constructor";
        }

        testdoc_t get_docs()
        {
            return "Create a new LayerInstance object and test the copy constructor.";
        }

        bool run()
        {
            Matrix3d test_matrix;
            test_matrix << 1,2,3,
                           4,5,6,
                           7,8,9;
            Transformation test_transform = Transformation(test_matrix);
            LayerInstance test_instance_one = LayerInstance(test_transform);
            // Create a new matrix for a new transform, which will be used for a new LayerInstance
            test_matrix << 9,8,7,
                           6,5,4,
                           3,2,1;
            test_transform = Transformation(test_matrix);
            // Set something up beforehand so it isn't null
            LayerInstance test_instance_two = LayerInstance(test_transform);
            // Copy
            test_instance_two = LayerInstance(test_instance_one);

            for (int i = 0; i < DIMENSION; i++)
            {
                for (int j = 0; j < DIMENSION; j++)
                {
                    PL_ASSERT_EQUAL(test_instance_two.transform.the_matrix(i, j), test_instance_one.transform.the_matrix(i, j));
                }
            }
            return true;
        }
};

class TestSuite_LayerInstance : public TestSuite
{
    public:
        testdoc_t get_title()
        {
            return "LayerInstance Tests";
        }

        void load_tests();
};
#endif