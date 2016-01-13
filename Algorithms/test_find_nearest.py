from unittest import TestCase

find_near = __import__('3_find_near')


class TestFind_nearest(TestCase):
    def test_find_nearest_one_elem(self):
        a = [10]

        result = find_near.find_nearest(a, 1)
        self.assertEquals(result, 0)

        result = find_near.find_nearest(a, 10)
        self.assertEquals(result, 0)

        result = find_near.find_nearest(a, 11)
        self.assertEquals(result, 0)

    def test_find_nearest_elem(self):
        a = [10, 20, 30]

        result = find_near.find_nearest(a, 9)
        self.assertEquals(result, 0)

        result = find_near.find_nearest(a, 15)
        self.assertEquals(result, 0)

        result = find_near.find_nearest(a, 16)
        self.assertEquals(result, 1)

        result = find_near.find_nearest(a, 20)
        self.assertEquals(result, 1)

        result = find_near.find_nearest(a, 24)
        self.assertEquals(result, 1)

        result = find_near.find_nearest(a, 25)
        self.assertEquals(result, 1)

        result = find_near.find_nearest(a, 35)
        self.assertEquals(result, 2)

    def test_find_nearest_5t(self):
        a = [1, 2, 3, 50, 60, 70, 80, 90, 100, 110]

        result = find_near.find_nearest(a, 59)
        self.assertEquals(result, 4)
