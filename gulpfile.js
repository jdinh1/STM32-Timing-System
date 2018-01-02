var gulp = require('gulp');
var format = require('gulp-clang-format');

var cppFiles = [
	'src/*.cpp',
	'test/**/*.cpp',
	'lib/**/*.cpp',
	'lib/**/*.h',
	'!lib/PB/*',
	'!lib/Test/*'
];

gulp.task('check-format', function() {
	return gulp.src(cppFiles)
		.pipe(format.checkFormat('file', undefined, {verbose: true, fail: true}));
});

gulp.task('format', function() {
	// The base option ensures the glob doesn't strip prefixes
	return gulp.src(cppFiles, {base: '.'})
		.pipe(format.format('file', undefined, {verbose: true, fail: true}))
		.pipe(gulp.dest('.'));
});

