# HTLL – Hyper Text Lisp Language
A hypertext language with lisp-like syntax, translated into HTML.

## Building
Compile by running `make`.

## Usage
```
Usage: htll [-ugly] <file>
```

## What does this do?
HTLL transpiles this:
```htll
(html :lang la
(head

(title Lorem ipsum)
(style :type text/css
	h1 {
		font-family: sans-serif;
	}
)

)(body

(h1 Lorem ipsum)
(hr)
(p
	Quod ducimus expedita minus neque rerum. Aut doloremque minus temporibus quaerat non neque.
	Commodi sed quas deserunt quasi in. Voluptas sit doloribus similique quibusdam voluptatum
	voluptatem. Et iure quis velit animi voluptate doloribus. Provident earum consequatur
	accusantium vel neque et non eos.)
(p
	Odit sunt itaque veniam eum eum. Excepturi aperiam aut nam distinctio minus.
	Sit at provident temporibus temporibus consequatur dolor.)
(p
	Vitae dolorem veniam illum fuga est. Et possimus dolore nobis voluptas enim ratione.
	Velit et ut omnis porro aut. Quia ut et accusamus qui ex ex ducimus et.
	Aut ullam autem autem quia omnis sint incidunt.)
(p
	Fugit soluta voluptate adipisci expedita quisquam quia voluptatum qui. Et aperiam omnis
	error velit et et provident iste. Quibusdam distinctio modi voluptatem consectetur quia
	nesciunt. Necessitatibus voluptate quod recusandae voluptate officiis.)
(p
	Neque qui nisi illum beatae velit. Quisquam sequi accusantium dolorum doloremque veritatis
	quo molestiae. Ullam quidem omnis nisi repudiandae veritatis fuga.
	Quo culpa quis harum cupiditate vel.)

)))
```
into this:
```html
<html lang="la">
<head>
<title>
Lorem ipsum
</title>
<style type="text/css">
h1 {
		font-family: sans-serif;
	}

</style>

</head>
<body>
<h1>
Lorem ipsum
</h1>
<hr/>
<p>
Quod ducimus expedita minus neque rerum. Aut doloremque minus temporibus quaerat non neque.
	Commodi sed quas deserunt quasi in. Voluptas sit doloribus similique quibusdam voluptatum
	voluptatem. Et iure quis velit animi voluptate doloribus. Provident earum consequatur
	accusantium vel neque et non eos.
</p>
<p>
Odit sunt itaque veniam eum eum. Excepturi aperiam aut nam distinctio minus.
	Sit at provident temporibus temporibus consequatur dolor.
</p>
<p>
Vitae dolorem veniam illum fuga est. Et possimus dolore nobis voluptas enim ratione.
	Velit et ut omnis porro aut. Quia ut et accusamus qui ex ex ducimus et.
	Aut ullam autem autem quia omnis sint incidunt.
</p>
<p>
Fugit soluta voluptate adipisci expedita quisquam quia voluptatum qui. Et aperiam omnis
	error velit et et provident iste. Quibusdam distinctio modi voluptatem consectetur quia
	nesciunt. Necessitatibus voluptate quod recusandae voluptate officiis.
</p>
<p>
Neque qui nisi illum beatae velit. Quisquam sequi accusantium dolorum doloremque veritatis
	quo molestiae. Ullam quidem omnis nisi repudiandae veritatis fuga.
	Quo culpa quis harum cupiditate vel.
</p>

</body>

</html>
```
Or an uglier version of the same code, if you think that a couple of newlines will screw you up.

## FAQ
- **Why?** I don't know, this would have potential if it were an actual lisp dialect though.
- **XYZ is transpiled incorrectly!** Yeah, there are tons of caveats not covered by HTLL.
  Notably I wouldn't recommend writing `(script ...)` tags with Javascript inside.
  Not only because you would be writing Javascript, but parentheses will be parsed as in
  any other element, and all hell will break loose.
