# CLI Example

Generate and verify an example DET. Output should match [drip-scripts UA1](https://github.com/tuupola/drip-scripts/tree/testing/testing#ua1)

```
$ make
$ ./det_generate <raa> <hda> <hi_hex>
$ ./det_verify <det_hex> <hi_hex>
```

## Example

```shell
$ ./det_generate 16376 16376 b41176c5b305e1823a47715c398f575dcc2a4f16bbdeebdc42d6518907f23b72
DET: 2001003ffe3ff80559921a9dbc5035d0

$ ./det_verify 2001003ffe3ff80559921a9dbc5035d0 b41176c5b305e1823a47715c398f575dcc2a4f16bbdeebdc42d6518907f23b72
DET: 2001003ffe3ff80559921a9dbc5035d0
Verification: OK
```
