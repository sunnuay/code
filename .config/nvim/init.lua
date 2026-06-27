vim.g.mapleader = " "
vim.opt.cmdheight = 0
vim.opt.expandtab = true
vim.opt.ignorecase = true
vim.opt.laststatus = 3
vim.opt.number = true
vim.opt.relativenumber = true
vim.opt.shiftwidth = 2
vim.opt.tabstop = 4
vim.keymap.set("n", "<C-s>", vim.cmd.update)
vim.keymap.set("n", "<leader>q", vim.cmd.quit)
vim.keymap.set("n", "<leader>h", vim.cmd.nohlsearch)
vim.keymap.set({ "n", "v" }, "<leader>y", '"+y')
vim.keymap.set({ "n", "v" }, "<leader>p", '"+p')

-- catppuccin/nvim
vim.pack.add({ { src = "https://github.com/catppuccin/nvim" } })
vim.cmd.colorscheme("catppuccin")

-- nvim-mini/mini.nvim
vim.pack.add({ { src = "https://github.com/nvim-mini/mini.nvim" } })
require("mini.ai").setup()
require("mini.diff").setup({ view = { style = "sign" } })
require("mini.files").setup({ windows = { preview = true } })
require("mini.icons").setup()
require("mini.move").setup()
require("mini.pairs").setup()
require("mini.pick").setup()
require("mini.statusline").setup()
vim.keymap.set("n", "<leader>d", MiniDiff.toggle_overlay)
vim.keymap.set("n", "<leader>e", MiniFiles.open)
vim.keymap.set("n", "<leader>f", MiniPick.builtin.files)
vim.keymap.set("n", "<leader>b", MiniPick.builtin.buffers)
vim.keymap.set("n", "<leader>s", MiniPick.builtin.grep_live)

-- folke/flash.nvim
vim.pack.add({ { src = "https://github.com/folke/flash.nvim" } })
require("flash").setup()
vim.keymap.set("n", "s", require("flash").jump)

-- akinsho/toggleterm.nvim
vim.pack.add({ { src = "https://github.com/akinsho/toggleterm.nvim" } })
require("toggleterm").setup({ open_mapping = "<C-/>" })
local Terminal = require("toggleterm.terminal").Terminal
local lazygit = Terminal:new({ cmd = "lazygit", direction = "float" })
vim.keymap.set("n", "<leader>g", function()
	lazygit:toggle()
end)

-- saghen/blink.cmp
vim.pack.add({ { src = "https://github.com/saghen/blink.cmp", version = "v1" } })
require("blink.cmp").setup({ keymap = { preset = "enter" } })

-- neovim/nvim-lspconfig
vim.pack.add({ { src = "https://github.com/neovim/nvim-lspconfig" } })
vim.lsp.enable({ "clangd", "gopls", "ty", "ruff", "vtsls" })
vim.lsp.inlay_hint.enable(true)
vim.keymap.set("n", "gd", vim.lsp.buf.definition)
vim.keymap.set("n", "gr", vim.lsp.buf.references)
vim.keymap.set("n", "<leader>cr", vim.lsp.buf.rename)
vim.keymap.set("n", "<leader>ca", vim.lsp.buf.code_action)
vim.keymap.set("n", "<leader>cd", vim.diagnostic.setloclist)
vim.diagnostic.config({ virtual_lines = { current_line = true } })

-- stevearc/conform.nvim
vim.pack.add({ { src = "https://github.com/stevearc/conform.nvim" } })
require("conform").setup({
	format_on_save = { lsp_format = "fallback" },
	formatters_by_ft = {
		lua = { "stylua" },
		markdown = { "prettier" },
		html = { "prettier" },
		css = { "prettier" },
		javascript = { "prettier" },
		typescript = { "prettier" },
		javascriptreact = { "prettier" },
		typescriptreact = { "prettier" },
	},
})

-- :lua vim.pack.update()
