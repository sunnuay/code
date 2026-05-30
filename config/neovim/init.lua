vim.g.mapleader = " "

vim.o.cmdheight = 0
vim.o.laststatus = 3
vim.o.list = true
vim.o.number = true
vim.o.relativenumber = true
vim.o.shiftwidth = 2

vim.pack.add({
  "https://github.com/catppuccin/nvim",
  "https://github.com/nvim-mini/mini.nvim",
  "https://github.com/akinsho/toggleterm.nvim",
  "https://github.com/neovim/nvim-lspconfig",
  "https://github.com/saghen/blink.lib",
  "https://github.com/saghen/blink.cmp",
})

vim.cmd.colorscheme("catppuccin")

require("toggleterm").setup()
require("mini.diff").setup()
require("mini.icons").setup()
require("mini.move").setup()
require("mini.pairs").setup()
require("mini.pick").setup()
require("mini.statusline").setup()
require("mini.files").setup({ windows = { preview = true } })
require("blink.cmp").setup({
  keymap = { preset = "enter" },
  fuzzy = { implementation = "lua" },
})

vim.keymap.set("n", "q", "<Nop>")
vim.keymap.set("t", "<Esc>", [[<C-\><C-n>]])

vim.keymap.set({ "n", "v" }, "<leader>y", '"+y')
vim.keymap.set({ "n", "v" }, "<leader>d", '"+d')
vim.keymap.set({ "n", "v" }, "<leader>p", '"+p')

vim.keymap.set({ "n", "t" }, "<C-/>", vim.cmd.ToggleTerm)

vim.keymap.set("n", "<Esc>", vim.cmd.nohlsearch)
vim.keymap.set("n", "<C-s>", vim.cmd.update)

vim.keymap.set("n", "<leader>q", vim.cmd.quit)
vim.keymap.set("n", "<leader>e", MiniFiles.open)
vim.keymap.set("n", "<leader>f", MiniPick.builtin.files)
vim.keymap.set("n", "<leader>b", MiniPick.builtin.buffers)

vim.lsp.inlay_hint.enable(true)
vim.lsp.enable({ "pyright", "clangd" })

vim.diagnostic.config({
  virtual_text = true,
})

vim.api.nvim_create_autocmd("BufWritePre", {
  pattern = "*.cpp",
  callback = function()
    vim.lsp.buf.format()
  end,
})

vim.api.nvim_create_autocmd("TextYankPost", {
  callback = function()
    vim.highlight.on_yank()
  end,
})

vim.keymap.set("n", "gd", vim.lsp.buf.definition)
vim.keymap.set("n", "gD", vim.lsp.buf.declaration)
vim.keymap.set("n", "gi", vim.lsp.buf.implementation)
vim.keymap.set("n", "gr", vim.lsp.buf.references)

vim.keymap.set("n", "<leader>rn", vim.lsp.buf.rename)
vim.keymap.set("n", "<leader>ca", vim.lsp.buf.code_action)
