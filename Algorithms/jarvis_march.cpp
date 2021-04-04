#include <opencv2/highgui/highgui.hpp>
#include <opencv2/photo.hpp>

using namespace cv;
using namespace std;

#define w 400

// pq cross pr
int orientation(Point p, Point q, Point r) {
	int cross = (q.x - p.x) * (r.y - q.y) - (r.x - q.x) * (q.y - p.y);
	if (cross == 0) {
		return 0;
	}
	if (cross > 0) {
		return 1; // r to q counter clockwise
	}
	return 2; // r to q clockwise

}

template<typename T>
struct has_const_iterator {
private:
	template<typename C> static char test(typename C::const_iterator*);
	template<typename C> static double test(...);

	static T t;
public:

	enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

template<typename Container>
typename std::enable_if<has_const_iterator<Container>::value, int>::type
memberSatuKali(const Container& C, typename Container::value_type const& t) {
	return C[0] * 2;
}


template<typename Container>
typename std::enable_if<has_const_iterator<Container>::value, Container>::type
jarvis(Container& points) {
	size_t n = points.size();

	if (n < 3) throw "Need at least 3 points";

	Container hull;
	int lowest = 0;

	for (int i = 0; i < n; ++i) {
		if (points[i].y < points[lowest].y) {
			lowest = i;
		}
	}

	int p = lowest;
	int q;

	do {
		hull.push_back(points[p]);
		q = (p + 1) % n;
		for (int i = 0; i < n; ++i) {
			if (orientation(points[p], points[i], points[q]) == 1) {
				q = i;
			}
		}
		p = q;
	} while (p != lowest);

	return hull;
}


int main()
{
	String title = "Drawing line";

	const Point points[] = {
		Point(2, 1), Point(1, 3), Point(4, 2), Point(2, 3),
		Point(3, 4), Point(5, 4), Point(1, 5), Point(4, 5)
	};

	vector<Point> resize;
	for (int i = 0; i < 8; ++i) {
		resize.push_back(Point((points[i].x) * 50, (points[i].y) * 50));
	}


	vector<Point> hasil = jarvis(resize);

	Mat gambar(w, w, CV_8U, Scalar(0));

	for (int i = 0; i < resize.size(); ++i) {
		circle(gambar, resize[i], 2, Scalar(255, 255, 255), 1);
	}

	polylines(gambar, hasil, 1, Scalar(255, 255, 255), 2);

	imshow("hasil", gambar);
	int k = waitKey(0);


	return 0;
}
